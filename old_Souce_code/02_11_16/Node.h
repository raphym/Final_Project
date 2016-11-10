#ifndef Node_H
#define Node_H
#include "malloc.h"
#include <vector>
#include <string>
#include <cmath>
#define DISTANCE 40

class Node
{
    public:
        Node(std::string n,double x, double y , int i);
        virtual ~Node();
        std::string getName();
        int getId();
        double getLocationX();
        double getLocationY();
        bool isCoverage();
        void setCoverage(bool b);
        void send(int message,int idDest);
        void receive(int message,int idDest);
        void scanHotspots(Node **nodes,int theSize);
        void printAvailableNodes();
        int getNbAvailableNodes();
        Node** getVectAvailableNodes();








    protected:
      std::string *name;
      int id;
      double locationX;
      double locationY;
      bool   coverage;
      Node **availableNodes;
      int nbAvailableNodes;




    private:

};

#endif // Node_H
