#ifndef MAP_H
#define MAP_H
#include "FileStream.h"
#include "string"

#include "Lamp.h"
#include "Provider.h"
#include "TrafficLight.h"
#include "Node.h"

#include <stdlib.h>     /* atof */
#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>



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
        std::vector<Node*> getNodes(); // return a vectors of all elements of the map (nodes)
        void addNode(Node *n); // add a node
        void removeNode(int id); // remove a node

protected:

private:
        //Node **elementsOfTheMap; //storage of all the elements of the map
        int nbLamps; //num of lamps
        int nbProviders; // num of provider
        int nbTrafficLight; // num of trafficLight
        std::vector<Node*> vecElementsOfTheMap;

};

#endif // MAP_H
