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
Simulation(std::string city); //constructor
virtual ~Simulation(); //Destructor
void startSim(); //start the Simulation
void sendRequests(); //send Requests according to the Events-Schedule
void sendRequestsTest(); //send Requests n*n TEST Queries
void networkSend(int idSource,int idDest,ObjectRequest *obj); //the network send , this function mimics the wifi sending
std::string getRandomId(int len, int i); //get a Random Id for a packet
void split(std::string& s, char delim,std::vector<std::string>& v); //function which split a string into a vector
void printVector(std::string vectorName, std::vector<int> vec); //function which print a Vector
void printArray(std::string vectorName, int* arr, int nums); //function which print an array
int searchMaxInVector(std::vector<int>v); //function which search the max in a vector
int* constructAnalysisGraph(std::vector<int>v, int nums); //construct Analysis Graph
void writeDataGraph(int *analysisGraph,int nums,std::string name); //write Data Graph


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
