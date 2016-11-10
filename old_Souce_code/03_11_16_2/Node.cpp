#include "Node.h"

using namespace std;
static int next_id=0;


Node::Node(string n,double x, double y)//ctor
{
    name = new string(n);
    locationX = x;
    locationY = y;
    id=next_id;
    next_id= next_id + 1;
    coverage=false;
    nbAvailableNodes=0;
    availableNodes =NULL;
}

Node::~Node()//dtor
{
  delete name;
  delete [] availableNodes;
}
int Node::getId()
{
    return id;
}
string Node::getName()
{
    return *name;
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



void Node::send(int message,int idDest)
{

}

void Node::receive(int message,int idDest)
{

}


void Node::scanHotspots(Node **nodes,int theSize)
{

  //if there is already vector of hotspots
  if (availableNodes!=NULL)
    delete [] availableNodes;


  int i=0;
  int counter=0;


  for(i=0 ; i< theSize ; i++)
  {
    double diffX = abs(nodes[i]->getLocationX() - this->getLocationX());
    double diffY = abs(nodes[i]->getLocationY() - this->getLocationY());

    if(diffX <= DISTANCE || diffY <= DISTANCE)
      if(this->getId() != nodes[i]->getId())
        counter++;
  }
  availableNodes = new Node*[counter];
  nbAvailableNodes =counter;

  int j=0;
  for(i=0 ; i< theSize ; i++)
  {
    double diffX = abs(nodes[i]->getLocationX() - this->getLocationX());
    double diffY = abs(nodes[i]->getLocationY() - this->getLocationY());

    if(diffX <= DISTANCE || diffY <= DISTANCE)
    {
      if(this->getId() != nodes[i]->getId())
      {
        availableNodes[j]=nodes[i];
        j++;
      }
    }
  }
}

void Node::printAvailableNodes()
{
  int i=0;
  for(i=0 ; i<nbAvailableNodes ; i++)
  {
    if (i==0)
    cout << "[" <<  availableNodes[0]->getName() << ",";

    else if (i==nbAvailableNodes -1 )
    cout << availableNodes[i]->getName() << "]"<<endl;

    else
    cout << availableNodes[i]->getName() << ",";
  }
}

int Node::getNbAvailableNodes()
{
  return nbAvailableNodes;
}

Node** Node::getVectAvailableNodes()
{
  return availableNodes;
}
