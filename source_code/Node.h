#ifndef Node_H
#define Node_H
#include <string>
#include <vector>
#include <iostream>
#include <cmath>
#define DISTANCE 40

class Node
{
public:
Node(std::string type,std::string n,double x, double y);
virtual ~Node();
std::string getName();         //return the name
int getId();         //return the id
double getLocationX();         //return the location x
double getLocationY();         //return the location y
std::string getType();
void send(int message,int idSource,int idDest);         // to send a message
void receive(int message,int idSource,int idDest);         // to receive a message
void scanHotspots(std::vector<Node*>);         //to scan the area
std::vector<Node*> getVectAvailableNodes();         // return the vector which contains all the elements present in the area
void printAvailableNodes();         // print the elements present in the area
bool checkIfBusy();         // to check if a node is busy
void setIsBusy(bool b);         // to set the availability of a node
void erase();         // Erase the node
bool checkIfErased();         // to check if a node is Erased
int getVisited();
void setVisited();
std::vector<int> getlistOfQuorum();
void addTolistOfQuorum(int id);




protected:
std::string *name;         //name of the node
std::vector<Node*> vecAvailableNodes;
std::vector <int> listOfQuorum;



int id;         //id of the node
double locationX;         //location x of the node
double locationY;         // location Y of the node
std::string type;

bool isBusy;         // status of the node
bool isErased;         // bool to know if the node is erased
int visited;
private:
};

#endif // Node_H
