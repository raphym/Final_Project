#ifndef SIMULATION_H
#define SIMULATION_H
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "Map.h"
#include "Node.h"
#include "ObjectRequest.h"
#include "base64.h"


class Simulation
{
public:
Simulation(std::string city);
virtual ~Simulation();
void sendRequests();
std::string getRandomId(int len , int i);
void startSim();
void networkSend(int idSource,int idDest,ObjectRequest *obj);
void split(std::string& s, char delim,std::vector<std::string>& v);
void sendRequestsTest();

protected:
Map *theMap;
double nbSuccess;
double nbFailures;
double nbRequests;

private:

};





#endif // SIMULATION_H
