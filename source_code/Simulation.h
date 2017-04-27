#ifndef SIMULATION_H
#define SIMULATION_H

#include <string>
#include <iostream>
#include <vector>
#include "Map.h"
#include "Node.h"
#include "ObjectRequest.h"


class Simulation
{
public:
Simulation(std::string city);
virtual ~Simulation();
void sendRequest();
std::string getRandomId();
char genRandom();
void startSim();
void networkSend(int idSource,int idDest,ObjectRequest *obj);


protected:
Map *theMap;
private:

};





#endif // SIMULATION_H
