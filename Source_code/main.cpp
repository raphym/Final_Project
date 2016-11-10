#include <vector>
#include <fstream>
#include <iostream>

#include "Lamp.h"
#include "Provider.h"
#include "TrafficLight.h"

#include "Map.h"
#include "FileStream.h"
#include <malloc.h>
using namespace std;

int main(int argc, char *argv[])
{
        Map map;

        map.getNodes()[0]->scanHotspots(map.getNodes());
        map.getNodes()[1]->scanHotspots(map.getNodes());
        map.getNodes()[2]->scanHotspots(map.getNodes());
        map.getNodes()[3]->scanHotspots(map.getNodes());

        map.PrintMap();
        cout << "----------------------------------------------------------------------------------"<<endl;
        cout <<endl;

        map.getNodes()[1]->send(58,1,0);
        cout <<endl;
        map.removeNode(0);
        map.getNodes()[0]->scanHotspots(map.getNodes());
        map.getNodes()[1]->scanHotspots(map.getNodes());
        map.getNodes()[2]->scanHotspots(map.getNodes());

        map.PrintMap();
        cout << "afterRemove" << endl<<endl;
        map.getNodes()[1]->send(58,1,0);

        cout <<endl;

        return 0;
}
