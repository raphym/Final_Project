#ifndef Node_H
#define Node_H
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <cmath>

#include "ObjectRequest.h"

#define DISTANCE 40
#define New_Node_Id -2
#define INCREMENT 5
#define RESET 6


class Node
{
public:
Node(std::string type,std::string n,int theId,double x, double y);
virtual ~Node();
std::string getName();         //return the name
int getId();         //return the id
double getLocationX();         //return the location x
double getLocationY();         //return the location y
std::string getType();
void send(int message,int idSource,int idDest);         // to send a message
void receive(int message,int idSource,int idDest);         // to receive a message
void scanHotspots(std::vector<Node*> inputNodes, std::vector<Node*> &outputNodes ); //to scan the area
std::vector<Node*>& getVectAvailableNodes();         // return the vector which contains all the elements present in the area
void printAvailableNodes();         // print the elements present in the area
bool checkIfBusy();         // to check if a node is busy
void setIsBusy(bool b);         // to set the availability of a node
void erase();         // Erase the node
bool checkIfErased();         // to check if a node is Erased
int getVisited();
void setVisited(int choice);
std::vector<int> getlistOfQuorum();
void addTolistOfQuorum(int id);
bool isItBackbone();
void setToBeBackbone();
std::vector<std::vector<int> >& getTheTraceroute();
void printTraceroute(); //print the traceroute for each node


void sendRequest(int idSource,int idDest,std::string message);
void send(int idSource,int idDest,std::string message,ObjectRequest *obj);         // to send a message
void receive(int idSource,int idDest,std::string message,ObjectRequest *obj);         // to receive a message
void sendResponse(int idPacket,int idSource,int idDest,std::vector<int> &tracerouteBack);
bool checkIfExist(std::vector<int>vec,int id);

#define PACKET_ID_CREATOR 1000



protected:
std::string *name;         //name of the node
//this list is the WIFI reception.
std::vector<Node*> vecAvailableNodes;

// if a node is a backbone so the list will be the nodes it controls.
// if a node is not a backbone so the list will be the node (backbone) they control it.
std::vector <int> listOfQuorum;

//vectors for traceroute
std::vector<std::vector<int> >theTraceroute;


int id;         //id of the node
double locationX;         //location x of the node
double locationY;         // location Y of the node
std::string type;

bool isBusy;         // status of the node
bool isErased;         // bool to know if the node is erased
int visited;
bool isBackbone; // to know if the node is a backbone


private:
};

#endif // Node_H
