#ifndef MAP_H
#define MAP_H
#include "FileStream.h"
#include "string"

#include "Lamp.h"
#include "Provider.h"
#include "TrafficLight.h"

#include <stdlib.h>     /* atof */
#include <cmath>
#include <fstream>
#include <iostream>


class Map
{
public:
        Map();
        virtual ~Map();
        Lamp** loadLamps(); //return the Lamps vector on the boot
        Provider** loadProviders(); // return the Providers vector on the boot
        TrafficLight** loadTrafficLights(); // return the TrafficLights vector on the boot
        void loadMap(); // Load the entire map to the memory
        void PrintMap(); // print the map
        Node** getNodes(); // return a vectors of all elements of the map (nodes)
        int getNumOfElements(); //return the num of the elements in the map
        void addNode(Node *n);
        void removeNode(int id);

protected:

private:
        Node **elementsOfTheMap;
        int nbLamps;
        int nbProviders;
        int nbTrafficLight;
        int nbOfElements;
};

#endif // MAP_H
