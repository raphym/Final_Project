#ifndef Node_H
#define Node_H
#include <string>
#include <iostream>
#include <cmath>
#define DISTANCE 40

class Node
{
public:
        Node(std::string n,double x, double y);
        virtual ~Node();
        std::string getName(); //return the name
        int getId(); //return the id
        double getLocationX(); //return the location x
        double getLocationY(); //return the location y
        void send(int message,int idSource,int idDest); // to send a message
        void receive(int message,int idSource,int idDest); // to receive a message
        void scanHotspots(Node **nodes,int theSize); //to scan the area
        int getNbAvailableNodes(); //return the num of elements present in the area
        Node** getVectAvailableNodes(); // return the vector which contains all the elements present in the area
        void printAvailableNodes(); // print the elements present in the area
        bool checkIfBusy();
        void setIsBusy(bool b);

protected:
        std::string *name;
        int id;
        double locationX;
        double locationY;
        Node **availableNodes;
        int nbAvailableNodes;
        bool isBusy;

private:

};

#endif // Node_H
