#include "Backbone.h"
#include "malloc.h"

using namespace std;
///////////////////////////////////////////////////////////////////////////////
//constructor
//////////////////////////////////////////////////////////////////////////////
Backbone::Backbone(string type,string name,int theId,double x, double y,int max_hop) : Node(type,name,theId,x,y,max_hop)
{

}
///////////////////////////////////////////////////////////////////////////////
//Destructor
//////////////////////////////////////////////////////////////////////////////
Backbone::~Backbone() //dtor
{

}
///////////////////////////////////////////////////////////////////////////////
//print the members of the Quorum
//////////////////////////////////////////////////////////////////////////////
void Backbone::printQuorum(vector<Node*> vecElementsOfTheMap)
{
        Backbone *b = this;
        int size = b->getlistOfQuorum().size();
        string name = "Quorum of Backbone " + this->getName();
        cout << endl << name << " contains : ";
        for(int j=0; j< size; j++)
        {
                int id = b->getlistOfQuorum()[j];
                cout << " " <<  vecElementsOfTheMap[id]->getName();
        }
        cout << endl;
}
