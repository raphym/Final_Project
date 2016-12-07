#include "Node.h"

using namespace std;

Node::Node(string n,double x, double y , int i)//ctor
{
    name = new string(n);
    locationX = x;
    locationY = y;
    id=i;
    coverage=false;
}

Node::~Node()//dtor
{

}
int Node::getId()
{
    return id;
}
string Node::getName()
{
    return *name;
}

void Node::freeMemory()
{
  delete name;
}


double Node::getLocationX()
{
    return locationX;
}

double Node::getLocationY()
{
    return locationY;
}

bool Node::isCoverage()
{
    return coverage;
}

void Node::setCoverage(bool b)
{
    coverage =b;
}
