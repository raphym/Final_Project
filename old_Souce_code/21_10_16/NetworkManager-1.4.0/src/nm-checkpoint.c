/* -*- Mode: C; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/* NetworkManager -- Network link manager
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Copyright (C) 2016 Red Hat, Inc.
 */

#include "nm-default.h"
#include "nm-checkpoint.h"

#include <string.h>

#include "nm-auth-subject.h"
#include "nm-core-utils.h"
#include "nm-dbus-interface.h"
#include "nm-device.h"
#include "nm-manager.h"
#include "nm-settings.h"
#include "nm-settings-connection.h"
#include "nm-simple-connection.h"
#include "nm-utils.h"
#include "nmdbus-checkpoint.h"

#define _NMLOG_PREFIX_NAME                "checkpoint"
#define _NMLOG_DOMAIN                     LOGD_CORE

#define _NMLOG(level, ...) \
	G_STMT_START { \
		if (nm_logging_enabled (level, _NMLOG_DOMAIN)) { \
			char __prefix[32]; \
			\
			if (self) \
				g_snprintf (__prefix, sizeof (__prefix), "%s[%p]", ""_NMLOG_PREFIX_NAME"", (self)); \
			else \
				g_strlcpy (__prefix, _NMLOG_PREFIX_NAME, sizeof (__prefix)); \
			_nm_log ((level), (_NMLOG_DOMAIN), 0, \
			          "%s: " _NM_UTILS_MACRO_FIRST(__VA_ARGS__), \
			          __prefix _NM_UTILS_MACRO_REST(__VA_ARGS__)); \
		} \
	} G_STMT_END

typedef struct {
	char *original_dev_path;
	NMDevice *device;
	NMConnection *connection;
} DeviceCheckpoint;

typedef struct {
	/* properties */
	GHashTable *devices;
	gint64 created;
	guint32 rollback_timeout;
	/* private members */
	NMManager *manager;
	gint64 rollback_ts;
} NMCheckpointPrivate;

struct _NMCheckpoint {
	NMExportedObject parent;
	NMCheckpointPrivate priv;
};

typedef struct {
	NMExportedObjectClass parent;
} NMCheckpointClass;

G_DEFINE_TYPE (NMCheckpoint, nm_checkpoint, NM_TYPE_EXPORTED_OBJECT)

#define NM_CHECKPOINT_GET_PRIVATE(self) \
	({ \
		/* preserve the const-ness of self. Unfortunately, that
		 * way, @self cannot be a void pointer */ \
		typeof (self) _self = (self); \
		\
		/* Get compiler error if variable is of wrong type */ \
		_nm_unused const NMCheckpoint *_self2 = (_self); \
		\
		nm_assert (NM_IS_CHECKPOINT (_self)); \
		&_self->priv; \
	})

NM_GOBJECT_PROPERTIES_DEFINE_BASE (
	PROP_DEVICES,
	PROP_CREATED,
	PROP_ROLLBACK_TIMEOUT,
);

guint64
nm_checkpoint_get_rollback_ts (NMCheckpoint *self)
{
	g_return_val_if_fail (NM_IS_CHECKPOINT (self), 0);

	return NM_CHECKPOINT_GET_PRIVATE (self)->rollback_ts;
}

gboolean
nm_checkpoint_includes_device (NMCheckpoint *self, NMDevice *device)
{
	NMCheckpointPrivate *priv = NM_CHECKPOINT_GET_PRIVATE (self);

	return g_hash_table_contains (priv->devices, device);
}

GVariant *
nm_checkpoint_rollback (NMCheckpoint *self)
{
	NMCheckpointPrivate *priv = NM_CHECKPOINT_GET_PRIVATE (self);
	DeviceCheckpoint *dev_checkpoint;
	GHashTableIter iter;
	NMSettingsConnection *connection;
	NMDevice *device;
	GError *local_error = NULL;
	GVariantBuilder builder;

	_LOGI ("rollback of %s", nm_exported_object_get_path ((NMExportedObject *) self));
	 g_variant_builder_init (&builder, G_VARIANT_TYPE ("a{su}"));

	/* Start rolling-back each device */
	g_hash_table_iter_init (&iter, priv->devices);
	while (g_hash_table_iter_next (&iter, (gpointer *) &device, (gpointer *) &dev_checkpoint)) {
		gs_unref_object NMAuthSubject *subject = NULL;
		guint32 result = NM_ROLLBACK_RESULT_OK;
		const char *con_path;

		_LOGD ("rollback: restoring state of device %s", nm_device_get_iface (device));

		if (!nm_device_is_real (device)) {
			result = NM_ROLLBACK_RESULT_ERR_NO_DEVICE;
			_LOGD ("rollback: device is not realized");
			goto next_dev;
		}

		if (nm_device_get_state (device) <= NM_DEVICE_STATE_UNMANAGED) {
			result = NM_ROLLBACK_RESULT_ERR_DEVICE_UNMANAGED;
			_LOGD ("rollback: device is unmanaged");
			goto next_dev;
		}

		if (dev_checkpoint->connection) {
			/* The device had an active connection, check if the
			 * connection still exists
			 * */
			con_path = nm_connection_get_path (dev_checkpoint->connection);
			connection = nm_settings_get_connection_by_path (nm_settings_get(), con_path);

			if (connection) {
				/* If the connection is still there, restore its content
				 * and save it
				 * */
				_LOGD ("rollback: connection %s still exists", con_path);

				nm_connection_replace_settings_from_connection (NM_CONNECTION (connection),
				                                                dev_checkpoint->connection);
				nm_settings_connection_commit_changes (connection,
				                                       NM_SETTINGS_CONNECTION_COMMIT_REASON_NONE,
				                                       NULL,
				                                       NULL);
			} else {
				/* The connection was deleted, recreate it */
				_LOGD ("rollback: adding connection %s again", con_path);

				connection = nm_settings_add_connection (nm_settings_get (),
				                                         dev_checkpoint->connection,
				                                         TRUE,
				                                         &local_error);
				if (!connection) {
					_LOGD ("rollback: connection add failure: %s", local_error->message);
					g_clear_error (&local_error);
					result = NM_ROLLBACK_RESULT_ERR_FAILED;
					goto next_dev;
				}
			}

			/* Now re-activate the connection */
			subject = nm_auth_subject_new_internal ();
			if (!nm_manager_activate_connection (priv->manager,
			                                     connection,
			                                     NULL,
			                                     device,
			                                     subject,
			                                     &local_error)) {
				_LOGW ("rollback: reactivation of connection %s/%s failed: %s",
				       nm_connection_get_id ((NMConnection *) connection),
				       nm_connection_get_uuid ((NMConnection *	) connection),
				       local_error->message);
				g_clear_error (&local_error);
				result = NM_ROLLBACK_RESULT_ERR_FAILED;
				goto next_dev;
			}
		} else {
			/* The device was initially disconnected, deactivate any existing connection */
			_LOGD ("rollback: disconnecting device");

			if (   nm_device_get_state (device) > NM_DEVICE_STATE_DISCONNECTED
			    && nm_device_get_state (device) < NM_DEVICE_STATE_DEACTIVATING) {
				nm_device_state_changed (device,
				                         NM_DEVICE_STATE_DEACTIVATING,
				                         NM_DEVICE_STATE_REASON_USER_REQUESTED);
			}
		}

next_dev:
		g_variant_builder_add (&builder, "{su}", dev_checkpoint->original_dev_path, result);
	}

	return g_variant_new ("(a{su})", &builder);
}

static DeviceCheckpoint *
device_checkpoint_create (NMDevice *device,
                          GError **error)
{
	DeviceCheckpoint *dev_checkpoint;
	NMConnection *connection;
	const char *path;

	if (!nm_device_is_real (device)) {
		g_set_error (error,
		             NM_MANAGER_ERROR,
		             NM_MANAGER_ERROR_INVALID_ARGUMENTS,
		             "device '%s' is not realized",
		             nm_device_get_iface (device));
		return NULL;
	}

	if (nm_device_get_state (device) <= NM_DEVICE_STATE_UNMANAGED) {
		g_set_error (error,
		             NM_MANAGER_ERROR,
		             NM_MANAGER_ERROR_INVALID_ARGUMENTS,
		             "device '%s' is unmanaged",
		             nm_device_get_iface (device));
		return NULL;
	}

	path = nm_exported_object_get_path (NM_EXPORTED_OBJECT (device));

	dev_checkpoint = g_slice_new0 (DeviceCheckpoint);
	dev_checkpoint->device = g_object_ref (device);
	dev_checkpoint->original_dev_path = g_strdup (path);

	connection = nm_device_get_applied_connection (device);
	if (connection)
		dev_checkpoint->connection = nm_simple_connection_new_clone (connection);

	return dev_checkpoint;
}

static void
device_checkpoint_destroy (gpointer data)
{
	DeviceCheckpoint *dev_checkpoint = data;

	g_clear_object (&dev_checkpoint->connection);
	g_clear_object (&dev_checkpoint->device);
	g_free (dev_checkpoint->original_dev_path);

	g_slice_free (DeviceCheckpoint, dev_checkpoint);
}

static void
nm_checkpoint_init (NMCheckpoint *self)
{
	NMCheckpointPrivate *priv = NM_CHECKPOINT_GET_PRIVATE (self);

	priv->devices = g_hash_table_new_full (g_direct_hash, g_direct_equal,
	                                       NULL, device_checkpoint_destroy);
}

static void
get_all_devices (NMManager *manager, GPtrArray *devices)
{
	const GSList *list, *iter;
	NMDevice *dev;

	list = nm_manager_get_devices (manager);

	for (iter = list; iter; iter = g_slist_next (iter)) {
		dev = iter->data;

		if (!nm_device_is_real (dev))
			continue;
		if (nm_device_get_state (dev) <= NM_DEVICE_STATE_UNMANAGED)
			continue;
		/* We never touch assumed connections, unless told explicitly */
		if (nm_device_uses_assumed_connection (dev))
			continue;

		g_ptr_array_add (devices, dev);
	}
}

NMCheckpoint *
nm_checkpoint_new (NMManager *manager, GPtrArray *devices, guint32 rollback_timeout,
                   GError **error)
{
	NMCheckpoint *self;
	NMCheckpointPrivate *priv;
	DeviceCheckpoint *dev_checkpoint;
	NMDevice *device;
	guint i;

	g_return_val_if_fail (manager, NULL);
	g_return_val_if_fail (devices, NULL);
	g_return_val_if_fail (!error || !*error, NULL);

	if (!devices->len)
		get_all_devices (manager, devices);

	if (!devices->len) {
		g_set_error_literal (error,
		                     NM_MANAGER_ERROR,
		                     NM_MANAGER_ERROR_INVALID_ARGUMENTS,
		                     "no device available");
		return NULL;
	}

	self = g_object_new (NM_TYPE_CHECKPOINT, NULL);

	priv = NM_CHECKPOINT_GET_PRIVATE (self);
	priv->manager = manager;
	priv->created = nm_utils_monotonic_timestamp_as_boottime (nm_utils_get_monotonic_timestamp_ms (),
	                                                          NM_UTILS_NS_PER_MSEC);
	priv->rollback_timeout = rollback_timeout;
	priv->rollback_ts = rollback_timeout ?
	    (nm_utils_get_monotonic_timestamp_ms () + ((gint64) rollback_timeout * 1000)) :
	    0;

	for (i = 0; i < devices->len; i++) {
		device = (NMDevice *) devices->pdata[i];
		dev_checkpoint = device_checkpoint_create (device, error);
		if (!dev_checkpoint) {
			g_object_unref (self);
			return NULL;
		}
		g_hash_table_insert (priv->devices, device, dev_checkpoint);
	}

	return self;
}

static void
dispose (GObject *object)
{
	NMCheckpoint *self = NM_CHECKPOINT (object);
	NMCheckpointPrivate *priv = NM_CHECKPOINT_GET_PRIVATE (self);

	g_clear_pointer (&priv->devices, g_hash_table_unref);

	G_OBJECT_CLASS (nm_checkpoint_parent_class)->dispose (object);
}

static void
get_property (GObject *object, guint prop_id,
              GValue *value, GParamSpec *pspec)
{
	NMCheckpoint *self = NM_CHECKPOINT (object);
	NMCheckpointPrivate *priv = NM_CHECKPOINT_GET_PRIVATE (self);
	gs_free_slist GSList *devices = NULL;
	GHashTableIter iter;
	NMDevice *device;

	switch (prop_id) {
	case PROP_DEVICES:
		g_hash_table_iter_init (&iter, priv->devices);
		while (g_hash_table_iter_next (&iter, (gpointer *) &device, NULL))
			devices = g_slist_append (devices, device);
		nm_utils_g_value_set_object_path_array (value, devices, NULL, NULL);
		break;
	case PROP_CREATED:
		g_value_set_int64 (value, priv->created);
		break;
	case PROP_ROLLBACK_TIMEOUT:
		g_value_set_uint (value, priv->rollback_timeout);
		break;
	default:
		G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
		break;
	}
}

static void
nm_checkpoint_class_init (NMCheckpointClass *checkpoint_class)
{
	GObjectClass *object_class = G_OBJECT_CLASS (checkpoint_class);
	NMExportedObjectClass *exported_object_class = NM_EXPORTED_OBJECT_CLASS (checkpoint_class);

	g_type_class_add_private (checkpoint_class, sizeof (NMCheckpointPrivate));

	exported_object_class->export_path = NM_DBUS_PATH "/Checkpoint/%u";
	exported_object_class->export_on_construction = FALSE;

	/* virtual methods */
	object_class->dispose = dispose;
	object_class->get_property = get_property;

	/* properties */
	obj_properties[PROP_DEVICES] =
	     g_param_spec_boxed (NM_CHECKPOINT_DEVICES, "", "",
	                         G_TYPE_STRV,
	                         G_PARAM_READABLE |
	                         G_PARAM_STATIC_STRINGS);

	obj_properties[PROP_CREATED] =
	    g_param_spec_int64 (NM_CHECKPOINT_CREATED, "", "",
	                        G_MININT64, G_MAXINT64, 0,
	                        G_PARAM_READABLE |
	                        G_PARAM_STATIC_STRINGS);

	obj_properties[PROP_ROLLBACK_TIMEOUT] =
	    g_param_spec_uint (NM_CHECKPOINT_ROLLBACK_TIMEOUT, "", "",
	                       0, G_MAXUINT32, 0,
	                       G_PARAM_READABLE |
	                       G_PARAM_STATIC_STRINGS);

	g_object_class_install_properties (object_class, _PROPERTY_ENUMS_LAST, obj_properties);

	nm_exported_object_class_add_interface (NM_EXPORTED_OBJECT_CLASS (checkpoint_class),
	                                        NMDBUS_TYPE_CHECKPOINT_SKELETON,
	                                        NULL);
}
