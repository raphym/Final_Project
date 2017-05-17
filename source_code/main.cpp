#include <iostream>
#include "Simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
        Simulation *s= new Simulation("Demo1");
        s->startSim();
        delete s;
}
