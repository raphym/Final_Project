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
        void loadLamps();
        void loadProviders();
        void loadTrafficLights();
        void loadMap();
        void printLamps();
        void printProviders();
        void PrintMap();
        void checkCoverage();
        Node** getNodes();
        int getNumOfElements();
        void NodeScan(int i);
        void updateMap();

protected:

private:
        Lamp **lamps;
        Provider **providers;
        TrafficLight **trafficLights;
        Node **elementsOfTheMap;

        int nbLamps;
        int nbProviders;
        int nbTrafficLight;
        int nbOfElements;


};

#endif // MAP_H
