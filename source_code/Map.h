#ifndef MAP_H
#define MAP_H
#include <string>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <queue>          // std::queue
#include <sstream>
#include <iomanip>
#include "FileStream.h"
#include "Node.h"
#include "Backbone.h"
#define MAX_BFS 4


class Map
{
public:
Map(std::string name,std::string fileProviders, std::string fileLamps, std::string fileTrafficLights,int max_hop,int idStartConstructQuorum); //constructor
virtual ~Map(); //Destructor
std::vector<Node*> loadLamps(); //return the Lamps vector on the boot
std::vector<Node*> loadProviders(); // return the Providers vector on the boot
std::vector<Node*> loadTrafficLights(); // return the TrafficLights vector on the boot
int loadMap(); // Load the entire map to the memory
void PrintMap(); // print the map
std::vector<Node*> getNodes(); // return a vectors of all elements of the map (nodes)
void addNode(Node *n); // add a node to the map
void removeNode(int id); // remove a node from the map
void refreshMap(); //Refresh the scan hotspots of each node in the map
void Garbage_Collector(); //clear the map of deleted elements
void quorumConstruct(); //Function which construct the quorums it's running the function runBFS
std::vector<Node*> runBFS(Node*); //Function which running BFS on a single Node
void printListOfQuorum(); //print the quorums
bool check(std::vector<Node*> bfsNodes,int id); //check if a specific Node exists in the vector
bool check(std::vector<int> bfsNodes,int id); //check if a specific Node id exists in the vector
void resetVisited(); //reset the feature reset of e specific Node (if 0 white , 1 grey , 2 black)
void printTraceroute(); //print the Traceroute of each node
void constructAllTraceroute(); //Construct the traceroutes for the nodes of the graph
void constructTraceroute(int idSource); //Construct a traceroute for a specific node
void recursiveDFS(int idSource,int idOrigin, bool visited[],int path[], int &path_index); //run DFS recursive to construct a traceroute
bool checkPbInLoading(); //check if there is a pb in the loading of the map
void writeQuorums();
void writeTraceroutes();
void writeMap();
std::string to_string_with_precision(double a_value,int n);


protected:
std::string name; //name of the map
std::string fileProviders; // file input providers
std::string fileLamps; //file input lamps
std::string fileTrafficLights; //file input trafficLights
std::vector<Node*> vecElementsOfTheMap; //vector of all elements of the map
bool pbInLoading; // bool to check if there is a pb in the loading of the map
int max_hop; //the max hop for the sending
int idStartConstructQuorum;//the id to start to construct the quorum

private:

};

#endif // MAP_H
