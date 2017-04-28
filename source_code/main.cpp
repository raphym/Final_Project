#include <iostream>
#include "Simulation.h"

using namespace std;

int main(int argc, char *argv[])
{

        Simulation *s= new Simulation("Paris-Eiffel");
        //s->sendRequest();
        s->startSim();
        delete s;

}
