#ifndef MAP_H
#define MAP_H
#include "string"
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <vector>

#include "FileStream.h"
#include "Node.h"
#include "Lamp.h"
#include "Provider.h"
#include "TrafficLight.h"

class Map
{
public:
        Map();
        virtual ~Map();
        std::vector<Lamp*> loadLamps(); //return the Lamps vector on the boot
        std::vector<Provider*> loadProviders(); // return the Providers vector on the boot
        std::vector<TrafficLight*> loadTrafficLights(); // return the TrafficLights vector on the boot
        void loadMap(); // Load the entire map to the memory
        void PrintMap(); // print the map
        std::vector<Node*> getNodes(); // return a vectors of all elements of the map (nodes)
        void addNode(Node *n); // add a node
        void removeNode(int id); // remove a node

protected:

private:
        std::vector<Node*> vecElementsOfTheMap;

};

#endif // MAP_H
