#include "Node.h"
#include "base64.h"

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

vector<vector<int> >&Node::getTheTraceroute()
{
        return theTraceroute;
}


void Node::printTraceroute()
{
        for(int i=0; i< theTraceroute.size(); i++)
        {
                cout << "List of " << this->getName() << " : " <<endl;

                for(int j=0; j< theTraceroute[i].size(); j++)
                {
                        cout << "{ ID : " << theTraceroute[i][j] <<" }"<< endl;
                }
                cout << endl;
        }
        cout << endl <<endl;
}


bool Node::checkIfExist(vector<int> vec,int id)
{
        for(int i=1; i<vec.size(); i++)
        {
                if(vec[i] == id)
                {
                        return true;
                }
        }

        return false;
}
bool Node::checkIfExist(vector<Node*> vec,int id)
{
        for(int i=1; i<vec.size(); i++)
        {
                if(vec[i]->getId() == id)
                {
                        return true;
                }
        }

        return false;
}

//function which split a string into a vector
void Node::split(const string& s, char delim,vector<string>& v)
{
        auto i = 0;
        auto pos = s.find(delim);
        while (pos != string::npos)
        {
                v.push_back(s.substr(i, pos-i));
                i = ++pos;
                pos = s.find(delim, pos);

                if (pos == string::npos)
                        v.push_back(s.substr(i, s.length()));
        }
}

bool Node::checkIfIsAlreadySend(string packetId,int idSource,int idDest)
{
        string line;
        vector<string> vecLineToCheck;
        ifstream myfile ("database.txt");
        if (myfile.is_open())
        {
                while ( getline (myfile,line) )
                {
                        split(line," ",vecLineToCheck);
                        if(vecLineToCheck[0] == packetId)
                        {
                                if(stoi(vecLineToCheck[1]) == idSource)
                                {
                                        if(stoi(vecLineToCheck[2]) == idDest)
                                        {
                                                return true;
                                        }
                                }
                        }
                }
                myfile.close();
                return false;
        }

        else cout << "Unable to open file";
        return false;
}

ObjectRequest* Node::send(ObjectRequest *obj)
{
        if(this->getId()==obj->getDestinationId())
        {
                obj->setMessageType("ACK");
                obj->popFromHeader();
                return obj;
        }

        if(obj->getmessageType()=="info")
        {
                if(obj->getHeader()[0]>= MAX_HOP)
                {
                        obj->setMessageType("NAK");
                        obj->popFromHeader();
                        return obj;
                }
                else
                {
                        int choiceToSend = -2;
                        for(int i=0; i<this->theTraceroute.size(); i++ )
                        {
                                if(this->theTraceroute[i].size()>0)
                                {
                                        if(checkIfExist(this->vecAvailableNodes, theTraceroute[i][0]) ==true)
                                        {
                                                choiceToSend = theTraceroute[i][0];
                                                break;
                                        }
                                }
                        }
                        obj->addToHeader(choiceToSend);
                        return obj;
                }

        }

        if(obj->getmessageType()=="NAK")
        {
                int choiceToSend = -2;
                bool found=false;
                for(int i=0; i<this->theTraceroute.size(); i++ )
                {
                        if(this->theTraceroute[i].size()>0)
                        {
                                if(checkIfExist(this->vecAvailableNodes, theTraceroute[i][0]) ==true)
                                {
                                        choiceToSend = theTraceroute[i][0];
                                        if(checkIfIsAlreadySend(obj->getPacketId(),obj->getSenderId(),obj->getDestinationId())==false)
                                        {
                                                found=true;
                                                break;
                                        }
                                }
                        }
                }
                if(found==true)
                {
                        obj->setMessageType("info");
                        obj->addToHeader(choiceToSend);
                        return obj;

                }
                if(found==false)
                {
                        obj->popFromHeader();
                        return obj;
                }

        }

        if(obj->getmessageType()=="ACK")
        {
                obj->popFromHeader();
                return obj;
        }
        return NULL;
}
