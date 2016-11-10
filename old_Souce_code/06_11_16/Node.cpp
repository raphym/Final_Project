#include "Node.h"

using namespace std;
static int next_id=0;


Node::Node(string n,double x, double y) //ctor
{
        name = new string(n);
        locationX = x;
        locationY = y;
        id=next_id;
        next_id= next_id + 1;
        nbAvailableNodes=0;
        availableNodes =NULL;
}

Node::~Node() //dtor
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



void Node::send(int message,int idSource,int idDest)
{
        bool sent=false;
        int i=0;
        for(i=0; i<nbAvailableNodes; i++)
        {
                if(this->availableNodes[i]->id == idDest)
                {
                        sent=true;
                        this->availableNodes[i]->receive(message,idSource,idDest);
                        break;
                }
        }

        if (sent == false)
        {
                cout << "Sorry ,there is no way for this moment. ";
                cout << "The node with id: "<< idSource << " cannot send any message ";
                cout << "to the node with the id: " << idDest <<endl;
        }
}

void Node::receive(int message,int idSource,int idDest)
{
        if(this->id == idDest)
        {
                cout << "The node with id: "<< this->id << " receive message number "<<message;
                cout << " From the node with the id :" << idSource <<endl;
        }
}


void Node::scanHotspots(Node **nodes,int theSize)
{

        //if there is already vector of hotspots
        if (this->availableNodes!=NULL)
                delete [] this->availableNodes;


        int i=0;
        int counter=0;


        for(i=0; i< theSize; i++)
        {
                double diffX = abs(nodes[i]->getLocationX() - this->getLocationX());
                double diffY = abs(nodes[i]->getLocationY() - this->getLocationY());

                if(diffX <= DISTANCE || diffY <= DISTANCE)
                        if(this->getId() != nodes[i]->getId())
                                counter++;
        }

        if(counter==0)
                return;

        this->availableNodes = new Node*[counter];
        this->nbAvailableNodes =counter;

        int j=0;
        for(i=0; i< theSize; i++)
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

        if(nbAvailableNodes==0)
                cout << "[]" << endl;
        for(i=0; i<nbAvailableNodes; i++)
        {
                if (i==0 && i == nbAvailableNodes-1)
                        cout << "[" <<  availableNodes[0]->getName()<< "(id:"<<availableNodes[0]->id<<")"<< "]" <<endl;

                else if (i==0)
                        cout << "[" <<  availableNodes[0]->getName()<< "(id:"<<availableNodes[0]->id<<")"<< ",";

                else if (i==nbAvailableNodes -1 )
                        cout << availableNodes[i]->getName()<< "(id:"<<availableNodes[i]->id<<")"<< "]"<<endl;

                else
                        cout << availableNodes[i]->getName()<< "(id:"<<availableNodes[i]->id<<")" << ",";
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
