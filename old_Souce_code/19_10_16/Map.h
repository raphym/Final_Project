#ifndef MAP_H
#define MAP_H
#include "Lamp.h"
#include "Provider.h"

#include <vector>
#include <string>


class Map
{
    public:
        Map();
        virtual ~Map();
        void printLamps();
        void printProviders();
        void PrintMap();
        void checkCoverage();


    protected:

    private:
        Lamp *lamps;
        Provider *providers;
        //std::vector<Lamp> lamps;

        int nbLinesLamps;
        int nbLinesProviders;

};

#endif // MAP_H
