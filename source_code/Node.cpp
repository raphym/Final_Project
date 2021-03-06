#include "Node.h"

using namespace std;
static int next_id=0;

///////////////////////////////////////////////////////////////////////////////
//constructor
//////////////////////////////////////////////////////////////////////////////
Node::Node(string type,string n,int theId,double x, double y,int max_hop)  //ctor
{
        this->type=type;
        this->name = new string(n);
        this->locationX = x;
        this->locationY = y;
        if(theId==New_Node_Id)
        {
                id=next_id;
                next_id= next_id + 1;
        }
        else
                this->id=theId;

        this->isBusy= false;
        this->isErased=false;
        this->visited=0;
        this->isBackbone=false;
        this->max_hop = max_hop;
}
///////////////////////////////////////////////////////////////////////////////
//destructor
//////////////////////////////////////////////////////////////////////////////
Node::~Node() //dtor
{
        delete name;
}
///////////////////////////////////////////////////////////////////////////////
//Get ID
//////////////////////////////////////////////////////////////////////////////
int Node::getId()
{
        return id;
}
///////////////////////////////////////////////////////////////////////////////
//Get Name
//////////////////////////////////////////////////////////////////////////////
string Node::getName()
{
        return *name;
}
///////////////////////////////////////////////////////////////////////////////
//Get LocationX
//////////////////////////////////////////////////////////////////////////////
double Node::getLocationX()
{
        return locationX;
}
///////////////////////////////////////////////////////////////////////////////
//Get LocationY
//////////////////////////////////////////////////////////////////////////////
double Node::getLocationY()
{
        return locationY;
}
///////////////////////////////////////////////////////////////////////////////
//set LocationX
//////////////////////////////////////////////////////////////////////////////
void Node::setLocationX(double newX)
{
        this->locationX=newX;
}
///////////////////////////////////////////////////////////////////////////////
//set LocationY
//////////////////////////////////////////////////////////////////////////////
void Node::setLocationY(double newY)
{
        this->locationY=newY;
}
///////////////////////////////////////////////////////////////////////////////
//get Type
//////////////////////////////////////////////////////////////////////////////
string Node::getType()
{
        return type;
}
///////////////////////////////////////////////////////////////////////////////
//check If a node is Busy
//////////////////////////////////////////////////////////////////////////////
bool Node::checkIfBusy()
{
        return isBusy;
}
///////////////////////////////////////////////////////////////////////////////
//set a node to be Busy
//////////////////////////////////////////////////////////////////////////////
void Node::setIsBusy(bool b)
{
        isBusy=b;
}
///////////////////////////////////////////////////////////////////////////////
//check If a node is Erased
//////////////////////////////////////////////////////////////////////////////
bool Node::checkIfErased()
{
        return isErased;
}
///////////////////////////////////////////////////////////////////////////////
//Erase a node
//////////////////////////////////////////////////////////////////////////////
void Node::erase()
{
        isErased=true;
}
///////////////////////////////////////////////////////////////////////////////
//return the boolean isItBackbone
//////////////////////////////////////////////////////////////////////////////
bool Node::isItBackbone()
{
        return isBackbone;
}
///////////////////////////////////////////////////////////////////////////////
//set the boolean isItBackbone
//////////////////////////////////////////////////////////////////////////////
void Node::setToBeBackbone()
{
        this->isBackbone = true;
}
///////////////////////////////////////////////////////////////////////////////
//set the max hop for the sending
//////////////////////////////////////////////////////////////////////////////
void Node::setMax_hop(int newMax_hop)
{
        this->max_hop = newMax_hop;
}
///////////////////////////////////////////////////////////////////////////////
//get the max hop for the sending
//////////////////////////////////////////////////////////////////////////////
int Node::getMax_hop()
{
        return this->max_hop;
}
///////////////////////////////////////////////////////////////////////////////
//wifi scan hotspot
//////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
//print the Available Nodes according to the wifi scan
//////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
//get the vector available nodes according to the wifi scan
//////////////////////////////////////////////////////////////////////////////
std::vector<Node*>&Node::getVectAvailableNodes()
{
        return vecAvailableNodes;
}
///////////////////////////////////////////////////////////////////////////////
//return the number visited (if 0 white , 1 grey , 2 black)
//////////////////////////////////////////////////////////////////////////////
int Node::getVisited()
{
        return this->visited;
}
///////////////////////////////////////////////////////////////////////////////
//set the number visited (if 0 white , 1 grey , 2 black)
//////////////////////////////////////////////////////////////////////////////
void Node::setVisited(int choice)
{
        if(choice==INCREMENT)
                this->visited+=1;

        else if(choice==RESET)
                this->visited=0;
}
///////////////////////////////////////////////////////////////////////////////
//Get the members of a quorum (list)
//////////////////////////////////////////////////////////////////////////////
vector<int> Node::getlistOfQuorum()
{
        return listOfQuorum;
}
///////////////////////////////////////////////////////////////////////////////
//add a member to the quorum list
//////////////////////////////////////////////////////////////////////////////
void Node::addTolistOfQuorum(int id)
{
        for(int i=0; i< this->listOfQuorum.size(); i++)
        {
                if(listOfQuorum[i]==id)
                        return;
        }
        listOfQuorum.push_back(id);
}
///////////////////////////////////////////////////////////////////////////////
//return the vector Traceroute (a vector to reach a backbone)
//////////////////////////////////////////////////////////////////////////////
vector<vector<int> >&Node::getTheTraceroute()
{
        return theTraceroute;
}
///////////////////////////////////////////////////////////////////////////////
//print the traceroutes (a vector to reach a backbone)
//////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
//Check if a node id exist in the header of the object request
//////////////////////////////////////////////////////////////////////////////
bool Node::checkIfExistInHeader(vector<int> vec,int id)
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
///////////////////////////////////////////////////////////////////////////////
//Check if a node id exist in a vector
//////////////////////////////////////////////////////////////////////////////
bool Node::checkIfExist(vector<int> vec,int id)
{
        for(int i=0; i<vec.size(); i++)
        {
                if(vec[i] == id)
                {
                        return true;
                }
        }

        return false;
}
///////////////////////////////////////////////////////////////////////////////
//Check if a node exist in a vector
//////////////////////////////////////////////////////////////////////////////
bool Node::checkIfExist(vector<Node*> vec,int id)
{
        for(int i=0; i<vec.size(); i++)
        {
                if(vec[i]->getId() == id)
                {

                        return true;
                }
        }

        return false;
}
///////////////////////////////////////////////////////////////////////////////
//The function send of a node
//////////////////////////////////////////////////////////////////////////////
ObjectRequest* Node::send(ObjectRequest *obj)
{
        //first check wifi connection if it is in the range
        for(int i=0; i<this->vecAvailableNodes.size(); i++)
        {
                if(this->vecAvailableNodes[i]->getId()==obj->getDestinationId())
                {
                        obj->setMessageType("ACK");
                        obj->addToHeader(this->vecAvailableNodes[i]->getId());
                        return obj;
                }
        }

        /*******************************************************************************************************************INFO*/
        //if the message is info
        if(obj->getmessageType()=="INFO")
        {
                //For debug
                cout << "INFO " << this->id<<endl;
                int index=0;
                bool canSend=false;

                //if arrived to destination
                if(this->id == obj->getDestinationId())
                {
                        obj->setMessageType("ACK");
                        return obj;
                }

                else //this->id != obj->getDestinationId()
                {
                        //If i am a backbone
                        if(this->isItBackbone())
                        {
                                //if it is the origin insert it to the visitedBackbone
                                if(this->id == obj->getSenderId())
                                        obj->addToVisitedBackbones(this->id);

                                bool foundInQuorum=false;

                                //check if the idDest isinside the quorum
                                for(int i=0; i< this->getlistOfQuorum().size(); i++)
                                {
                                        if(this->getlistOfQuorum()[i]==obj->getDestinationId())
                                        {
                                                foundInQuorum=true;
                                                break;
                                        }
                                }

                                if(foundInQuorum)
                                {
                                        //change the message to "info in Quorum"
                                        obj->setMessageType("INFO_IN_QUORUM");
                                        //check which traceroute can arrive to the destination
                                        for(index=0; index < this->getTheTraceroute().size(); index++)
                                        {
                                                if(canSend)
                                                {
                                                        break;
                                                }
                                                if(!checkIfExist(this->getTheTraceroute()[index], obj->getDestinationId()))
                                                        continue;

                                                //check already sent to this traceroute
                                                if(!checkIfExist(obj->getVisitedTraceroutes(),index))
                                                {
                                                        //add to the visited traceroute
                                                        obj->addToVisitedTraceroutes(index);
                                                        //check wifi connection
                                                        int idTosend = this->getTheTraceroute()[index][0];
                                                        for(int i=0; i<this->getVectAvailableNodes().size(); i++)
                                                        {
                                                                if(this->getVectAvailableNodes()[i]->getId()==idTosend)
                                                                {
                                                                        canSend=true;
                                                                        index--;
                                                                        break;
                                                                }
                                                                //Problem of WIFI
                                                                if(i==this->getVectAvailableNodes().size()-1)
                                                                {
                                                                        cout << "WIFI PROBLEM : The node disappeared "<<endl;
                                                                }
                                                        }
                                                }
                                        }
                                }

                                //if not in the quorum
                                else if(!foundInQuorum)
                                {
                                        //for the maxhop
                                        if(obj->getHeader()[0] == 1 && obj->getCounterBackbone() > this->max_hop)
                                        {
                                                obj->setMessageType("NAK");
                                                return obj;
                                        }
                                        if(obj->getCounterBackbone() > this->max_hop)
                                        {
                                                cout << "MAX_HOP (" <<obj->getCounterBackbone() << ")"<<endl;
                                                obj->setMessageType("NAK_INFO_TO_QUORUM");
                                                obj->popFromHeader();
                                                return obj;
                                        }
                                        //End max_hop
                                        obj->setMessageType("INFO_TO_QUORUM");
                                        //check which traceroute can arrive to a backbone
                                        for(index=0; index < this->getTheTraceroute().size(); index++)
                                        {
                                                if(canSend)
                                                {
                                                        break;
                                                }
                                                //check if already visited a backbone
                                                int idBackbone=this->getTheTraceroute()[index][this->getTheTraceroute()[index].size()-1];
                                                if(!checkIfExist(obj->getVisitedBackbones(),idBackbone))
                                                {
                                                        //check wifi connection
                                                        int idTosend = this->getTheTraceroute()[index][0];
                                                        for(int i=0; i<this->getVectAvailableNodes().size(); i++)
                                                        {
                                                                if(this->getVectAvailableNodes()[i]->getId()==idTosend)
                                                                {
                                                                        canSend=true;
                                                                        index--;
                                                                        //add to the visited backbone
                                                                        obj->addToVisitedBackbones(idBackbone);
                                                                        break;
                                                                }
                                                                //Problem of WIFI
                                                                if(i==this->getVectAvailableNodes().size()-1)
                                                                {
                                                                        cout << "WIFI PROBLEM : The node disappeared "<<endl;
                                                                }
                                                        }
                                                }
                                        }
                                }
                        }
                        //else if not backbone
                        else if(!this->isItBackbone())
                        {
                                obj->setMessageType("INFO_TO_QUORUM");
                                //check which traceroute can arrive to a backbone
                                for(index=0; index < this->getTheTraceroute().size(); index++)
                                {
                                        if(canSend)
                                        {
                                                break;
                                        }
                                        //check if already visited a backbone
                                        int idBackbone=this->getTheTraceroute()[index][this->getTheTraceroute()[index].size()-1];
                                        if(!checkIfExist(obj->getVisitedBackbones(),idBackbone))
                                        {
                                                //check wifi connection
                                                int idTosend = this->getTheTraceroute()[index][0];
                                                for(int i=0; i<this->getVectAvailableNodes().size(); i++)
                                                {
                                                        if(this->getVectAvailableNodes()[i]->getId()==idTosend)
                                                        {
                                                                canSend=true;
                                                                index--;
                                                                //add to the visited backbone
                                                                obj->addToVisitedBackbones(idBackbone);
                                                                break;
                                                        }
                                                        //Problem of WIFI
                                                        if(i==this->getVectAvailableNodes().size()-1)
                                                        {
                                                                cout << "WIFI PROBLEM : The node disappeared "<<endl;
                                                        }
                                                }
                                        }
                                }
                        }

                        if(canSend)
                        {
                                //copie the traceroute into the vector direction to execute
                                obj->clearDirectionToExecute();
                                for(int i=this->getTheTraceroute()[index].size()-1; i>=0; i--)
                                {
                                        obj->getDirectionToExecute().push_back( this->getTheTraceroute()[index][i] );
                                }

                                //begin to send
                                obj->addToHeader(obj->getDirectionToExecute().back());
                                obj->popFromDirectionToExecute();
                                return obj;
                        }
                        else if(!canSend)
                        {
                                if(obj->getHeader()[0]==1)
                                {
                                        obj->setMessageType("NAK");
                                        return obj;
                                }

                                if(obj->getmessageType() == "INFO_IN_QUORUM")
                                {
                                        obj->setMessageType("NAK_INFO_IN_QUORUM");
                                        obj->popFromHeader();
                                        return obj;
                                }

                                if(obj->getmessageType() == "INFO_TO_QUORUM")
                                {
                                        obj->setMessageType("NAK_INFO_TO_QUORUM");
                                        obj->popFromHeader();
                                        return obj;
                                }
                        }
                }
        }
        /*****************************************************************************************************************INFO_IN_QUORUM*/
        //if the message is info in quorum
        if(obj->getmessageType()=="INFO_IN_QUORUM")
        {
                //For debug
                cout << "INFO_IN_QUORUM " << this->id<<endl;

                //if it is the destination
                if(this->id==obj->getDestinationId())
                {
                        obj->setMessageType("ACK");
                        return obj;
                }

                //if the direction is empty return NAK_INFO_IN_QUORUM
                if(obj->getDirectionToExecute().size()==0)
                {
                        obj->setMessageType("NAK_INFO_IN_QUORUM");
                        obj->popFromHeader();
                        return obj;
                }
                else //if the direction is not empty , continue the sending
                {
                        //check wifi connection
                        int idTosend = obj->getDirectionToExecute().back();
                        for(int i=0; i<this->getVectAvailableNodes().size(); i++)
                        {
                                if(this->getVectAvailableNodes()[i]->getId()==idTosend)
                                {
                                        obj->addToHeader(obj->getDirectionToExecute().back());
                                        obj->popFromDirectionToExecute();
                                        return obj;
                                }
                                //Problem of WIFI
                                if(i==this->getVectAvailableNodes().size()-1)
                                {
                                        cout << "WIFI PROBLEM : The node disappeared INFO_IN_QUORUM in : " <<this->id <<endl;
                                        obj->setMessageType("NAK_INFO_TO_QUORUM");
                                        obj->popFromHeader();
                                        return obj;
                                }
                        }
                }
        }

        /***************************************************************************************************************NAK_INFO_IN_QUORUM*/

        //if the message is nak info in quorum
        if(obj->getmessageType()=="NAK_INFO_IN_QUORUM")
        {
                //For debug
                cout << "NAK_INFO_IN_QUORUM " << this->id<<endl;
                //We know that the node is in the quorum
                //We cannot found any ways to arrive to the destination
                //the traceroutes don't pass through this node
                //We will do brute force into the quorum

                for(int i=0; i<this->vecAvailableNodes.size(); i++)
                {
                        if(this->vecAvailableNodes[i]->getId()==obj->getDestinationId())
                        {
                                obj->setMessageType("ACK");
                                obj->addToHeader(this->vecAvailableNodes[i]->getId());
                                return obj;
                        }
                }
                //stop
                obj->setMessageType("NAK");
                return obj;
        }

        /***************************************************************************************************************INFO_TO_QUORUM*/
        //if the message is info to quorum
        if(obj->getmessageType()=="INFO_TO_QUORUM")
        {
                //For debug
                cout << "INFO_TO_QUORUM " << this->id<< " For backbone " << obj->getDirectionToExecute()[0]<< endl;

                //if it is the destination
                if(this->id==obj->getDestinationId())
                {
                        obj->setMessageType("ACK");
                        return obj;
                }

                //if arrive to the Quorum
                if(this->isItBackbone())
                {
                        //for the counter max hop
                        obj->incrementCounterBackbone();
                        obj->setMessageType("INFO");
                        return obj;
                }
                else //not arrived to backbone
                {
                        //if the directio is empty return NAK
                        if(obj->getDirectionToExecute().size()==0)
                        {
                                obj->setMessageType("NAK_INFO_TO_QUORUM");
                                obj->popFromHeader();
                                return obj;
                        }
                        else //if the direction is not empty , continue the sending to the backbone
                        {
                                //check wifi connection
                                int idTosend = obj->getDirectionToExecute().back();
                                for(int i=0; i<this->getVectAvailableNodes().size(); i++)
                                {
                                        if(this->getVectAvailableNodes()[i]->getId()==idTosend)
                                        {
                                                obj->addToHeader(obj->getDirectionToExecute().back());
                                                obj->popFromDirectionToExecute();
                                                return obj;
                                        }
                                        //Problem of WIFI
                                        //A verifier
                                        if(i==this->getVectAvailableNodes().size()-1)
                                        {
                                                cout << "WIFI PROBLEM : The node disappeared , INFO_TO_QUORUM in : "<< this->id<<endl;
                                                obj->setMessageType("NAK_INFO_TO_QUORUM");
                                                obj->popFromHeader();
                                                return obj;
                                        }
                                }
                        }
                }
        }

        /************************************************************************************************************NAK_INFO_TO_QUORUM*/
        //if the message is NAK INFO TO QUORUM
        if(obj->getmessageType()=="NAK_INFO_TO_QUORUM")
        {
                //For debug
                cout << "NAK_INFO_TO_QUORUM " << this->id<<endl;
                //if you not arrive to the origin so continue to go back
                if(!this->isItBackbone())
                {
                        if(obj->getHeader()[0]==1)
                                obj->setMessageType("NAK");
                        else
                                obj->popFromHeader();

                        return obj;
                }
                else //if you arrived to the origin
                {
                        //for the counter max hop
                        obj->decrementCounterBackBone();
                        obj->setMessageType("INFO");
                        return obj;
                }
        }
        return NULL;
}
///////////////////////////////////////////////////////////////////////////////
//END
//////////////////////////////////////////////////////////////////////////////
