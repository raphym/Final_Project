#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <iostream>
#include <vector>
#include "Map.h"
#include "Node.h"


class Simulation
{
public:
Simulation(std::string city);
virtual ~Simulation();
void sendRequest();


protected:
Map *theMap;
private:

};





#endif // SIMULATION_H
