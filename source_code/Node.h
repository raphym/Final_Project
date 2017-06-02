#ifndef Node_H
#define Node_H
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <cmath>
#include <fstream>

#include "ObjectRequest.h"
#include "base64.h"

#define DISTANCE 40
#define New_Node_Id -2
#define INCREMENT 5
#define RESET 6


class Node
{
public:
Node(std::string type,std::string n,int theId,double x, double y,int max_hop); //constructor
virtual ~Node(); //destructor
std::string getName(); //return the name
int getId(); //return the id
double getLocationX(); //return the location x
double getLocationY(); //return the location y
void setLocationX(double newX); //set the location x
void setLocationY(double newY); //set the location y
std::string getType(); //get the type
void scanHotspots(std::vector<Node*> inputNodes, std::vector<Node*> &outputNodes ); //to scan the area
std::vector<Node*>& getVectAvailableNodes(); // return the vector which contains all the elements present in the area
void printAvailableNodes(); // print the elements present in the area
bool checkIfBusy(); // to check if a node is busy
void setIsBusy(bool b); // to set the availability of a node
void erase(); // Erase the node
bool checkIfErased(); // to check if a node is Erased
int getVisited(); //return the number visited (if 0 white , 1 grey , 2 black)
void setVisited(int choice); //set the number visited (if 0 white , 1 grey , 2 black)
std::vector<int> getlistOfQuorum(); //Get the members of a quorum (list)
void addTolistOfQuorum(int id); //add a member to the quorum list
bool isItBackbone(); //return the boolean isItBackbone
void setToBeBackbone(); //set the boolean isItBackbone
std::vector<std::vector<int> >& getTheTraceroute(); //return the vector Traceroute (a vector to reach a backbone)
void printTraceroute(); //print the traceroute for each node
ObjectRequest* send(ObjectRequest *obj); // to send a message
bool checkIfExist(std::vector<int>vec,int id); //Check if a node id exist in the header of the object request
bool checkIfExist(std::vector<Node*>vec,int id); //Check if a node exist in the vector
bool checkIfExistInHeader(std::vector<int> vec,int id); //Check if a node id exist in the vector



protected:
std::string *name; //name of the node
//this list is the WIFI reception.
std::vector<Node*> vecAvailableNodes;

// if a node is a backbone so the list will be the nodes it controls.
// if a node is not a backbone so the list will be the node (backbone) they control it.
std::vector <int> listOfQuorum;

//vectors for traceroute
std::vector<std::vector<int> >theTraceroute;


int id; //id of the node
double locationX; //location x of the node
double locationY; // location Y of the node
std::string type;

bool isBusy; // status of the node
bool isErased; // bool to know if the node is erased
int visited; //visited for bfs
bool isBackbone; // to know if the node is a backbone
int max_hop;//the max of hop for the sending

private:
};

#endif // Node_H
