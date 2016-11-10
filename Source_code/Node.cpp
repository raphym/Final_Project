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
        isBusy= false;
        isErased=false;
}

Node::~Node() //dtor
{
        delete name;
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

bool Node::checkIfBusy()
{
        return isBusy;
}

void Node::setIsBusy(bool b)
{
        isBusy=b;
}

bool Node::checkIfErased()
{
        return isErased;
}

void Node::erase()
{
        isErased=true;
}
void Node::send(int message,int idSource,int idDest)
{
        bool sent=false;
        int i=0;
        for(i=0; i<vecAvailableNodes.size(); i++)
        {
                if(this->vecAvailableNodes[i]->id == idDest  && this->isBusy==false)
                {
                        this->isBusy=true;
                        sent=true;
                        this->vecAvailableNodes[i]->receive(message,idSource,idDest);
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
        int i;
        if(this->id == idDest)
        {
                cout << "The node with id: "<< this->id << " receive message number "<<message;
                cout << " From the node with the id :" << idSource <<endl;

                for(i=0; i<vecAvailableNodes.size(); i++)
                {
                        if(vecAvailableNodes[i]->id==idSource)
                                vecAvailableNodes[i]->isBusy=false;
                }
        }
}


void Node::scanHotspots(vector<Node*> vecNodes)
{

        //if there is already vector of hotspots
        if (this->vecAvailableNodes.size()!=0)
                vecAvailableNodes.clear();

        int i=0;
        int counter=0;
        double diffX=0;
        double diffY=0;

        for(i=0; i< vecNodes.size(); i++)
        {
                diffX = abs(vecNodes[i]->getLocationX() - this->getLocationX());
                diffY = abs(vecNodes[i]->getLocationY() - this->getLocationY());

                if(diffX <= DISTANCE || diffY <= DISTANCE)
                        if(this->getId() != vecNodes[i]->getId())
                                counter++;
        }

        if(counter==0)
          return;

        for(i=0; i< vecNodes.size(); i++)
        {
                diffX = abs(vecNodes[i]->getLocationX() - this->getLocationX());
                diffY = abs(vecNodes[i]->getLocationY() - this->getLocationY());

                if(diffX <= DISTANCE || diffY <= DISTANCE)
                {
                        if(this->getId() != vecNodes[i]->getId())
                        {
                                vecAvailableNodes.push_back(vecNodes[i]);
                        }
                }
        }
}

void Node::printAvailableNodes()
{
        int i=0;

        if(vecAvailableNodes.size()==0)
                cout << "[]" << endl;
        for(i=0; i<vecAvailableNodes.size(); i++)
        {
                if (i==0 && i == vecAvailableNodes.size()-1)
                        cout << "[" <<  vecAvailableNodes[0]->getName()<< "(id:"<<vecAvailableNodes[0]->id<<")"<< "]" <<endl;

                else if (i==0)
                        cout << "[" <<  vecAvailableNodes[0]->getName()<< "(id:"<<vecAvailableNodes[0]->id<<")"<< ",";

                else if (i==vecAvailableNodes.size() -1 )
                        cout << vecAvailableNodes[i]->getName()<< "(id:"<<vecAvailableNodes[i]->id<<")"<< "]"<<endl;

                else
                        cout << vecAvailableNodes[i]->getName()<< "(id:"<<vecAvailableNodes[i]->id<<")" << ",";
        }
}

std::vector<Node*> Node::getVectAvailableNodes()
{
        return vecAvailableNodes;
}
