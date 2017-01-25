#include "Node.h"

using namespace std;
static int next_id=0;

Node::Node(string type,string n,int theId,double x, double y)  //ctor
{
        this->type=type;
        name = new string(n);
        locationX = x;
        locationY = y;
        if(theId==New_Node_Id)
        {
                id=next_id;
                next_id= next_id + 1;
        }
        else
                this->id=theId;

        isBusy= false;
        isErased=false;
        visited=0;
        isBackbone=false;
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

string Node::getType()
{
        return type;
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

bool Node::isItBackbone()
{
        return isBackbone;
}

void Node::setToBeBackbone()
{
        this->isBackbone = true;
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


void Node::scanHotspots(vector<Node*> inputNodes, vector<Node*> &outputNodes )
{
        //the function check if a node is near to an another with a distance of 40 metters
        //I calculate according to the  Pythagorean theorem a^2+b^2 = c^2 < 40^2
        //vector input is the area and vector output is the result
        if (this->vecAvailableNodes.size()!=0)
                vecAvailableNodes.clear();

        double diffX=0;
        double diffY=0;
        double result=0;

        for(int i=0; i< inputNodes.size(); i++)
        {
                if(inputNodes[i]->checkIfErased()==true)
                        continue;
                diffX = abs(inputNodes[i]->getLocationX() - this->getLocationX());
                diffY = abs(inputNodes[i]->getLocationY() - this->getLocationY());
                result = sqrt( pow(diffX, 2) + pow(diffY, 2) );

                if(result <= 40 && this->getId() != inputNodes[i]->getId())
                        outputNodes.push_back(inputNodes[i]);


        }
}

// void Node::printAvailableNodes()
// {
//         if(vecAvailableNodes.size()==0)
//                 cout << "[]" << endl;
//         for(int i=0; i<vecAvailableNodes.size(); i++)
//         {
//                 if (i==0 && i == vecAvailableNodes.size()-1)
//                         cout << "[" <<  vecAvailableNodes[0]->getName()<< "(id:"<<vecAvailableNodes[0]->id<<")"<< "]" <<endl;
//
//                 else if (i==0)
//                         cout << "[" <<  vecAvailableNodes[0]->getName()<< "(id:"<<vecAvailableNodes[0]->id<<")"<< ",";
//
//                 else if (i==vecAvailableNodes.size() -1 )
//                         cout << vecAvailableNodes[i]->getName()<< "(id:"<<vecAvailableNodes[i]->id<<")"<< "]"<<endl;
//
//                 else
//                         cout << vecAvailableNodes[i]->getName()<< "(id:"<<vecAvailableNodes[i]->id<<")" << ",";
//         }
// }

void Node::printAvailableNodes()
{
        if(vecAvailableNodes.size()==0)
                cout << "[]" << endl;
        for(int i=0; i<vecAvailableNodes.size(); i++)
        {
                if (i==0 && i == vecAvailableNodes.size()-1)
                        cout << "[" <<  vecAvailableNodes[0]->getName()<< "]" <<endl;

                else if (i==0)
                        cout << "[" <<  vecAvailableNodes[0]->getName()<< ",";

                else if (i==vecAvailableNodes.size() -1 )
                        cout << vecAvailableNodes[i]->getName()<< "]"<<endl;

                else
                        cout << vecAvailableNodes[i]->getName() << ",";
        }
}

std::vector<Node*>&Node::getVectAvailableNodes()
{
        return vecAvailableNodes;
}

int Node::getVisited()
{
        return this->visited;
}

void Node::setVisited(int choice)
{
        if(choice==INCREMENT)
                this->visited+=1;

        else if(choice==RESET)
                this->visited=0;
}


vector<int> Node::getlistOfQuorum()
{
        return listOfQuorum;
}

void Node::addTolistOfQuorum(int id)
{
        for(int i=0; i< this->listOfQuorum.size(); i++)
        {
                if(listOfQuorum[i]==id)
                        return;
        }
        listOfQuorum.push_back(id);
}
