#include "Quorum.h"
#include "malloc.h"

using namespace std;

Quorum::Quorum(string type,string name,double x, double y) : Node(type,name,x,y)
{

}

Quorum::~Quorum() //dtor
{

}


void Quorum::printQuorum(vector<Node*> vecElementsOfTheMap)
{
        Quorum *q = this;
        int size = q->getlistOfQuorum().size();
        string name = "Quorum " + this->getName();
        cout << endl << name << " contains : " ;
        for(int j=0; j< size; j++)
        {
                int id = q->getlistOfQuorum()[j];
                cout << " " <<  vecElementsOfTheMap[id]->getName();
        }
        cout << endl;
}
