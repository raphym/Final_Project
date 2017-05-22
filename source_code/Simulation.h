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
void startSim();
std::string getRandomId(int len , int i);
void networkSend(int idSource,int idDest,ObjectRequest *obj);
void split(std::string& s, char delim,std::vector<std::string>& v);
void sendRequestsTest();
void printVector(std::string vectorName , std::vector<int> vec);
void printArray(std::string vectorName , int* arr, int nums);

int searchMaxInVector(std::vector<int>v);
int* constructAnalysisGraph(std::vector<int>v, int nums);
void writeDataGraph(int *analysisGraph,int nums,std::string name);



protected:
Map *theMap;
double nbSuccess;
double nbFailures;
double nbRequests;
int softwareHop;
int hardwareHop;
std::vector<int>vecOfSoftwareHop;
std::vector<int>vecOfHardwareHop;

private:

};





#endif // SIMULATION_H
