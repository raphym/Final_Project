#ifndef BACKBONE_H
#define BACKBONE_H
#include "Node.h"


class Backbone : public Node
{
public:
Backbone(std::string type,std::string n,int theId,double x, double y,int max_hop); //constructor
void printQuorum(std::vector<Node*> vecElementsOfTheMap); //print the members of the Quorum
virtual ~Backbone(); //Destructor


protected:

private:
};

#endif // BACKBONE_H
