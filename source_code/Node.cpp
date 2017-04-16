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

void Node::sendRequest(int idSource,int idDest,std::string message)
{
        int newId = this->id*PACKET_ID_CREATOR;
        string encoded = base64_encode(reinterpret_cast<const unsigned char*>(message.c_str()), message.length());
        ObjectRequest *obj = new ObjectRequest(newId,idSource,idDest,encoded);
        send(idSource,idDest,obj);
        delete obj;
}


void Node::send(int idSource,int idDest,ObjectRequest *obj)
{
        if(obj==NULL)
                return;
        cout << "SEND FROM " << idSource << " TO "<< idDest << endl;



        if(obj->checkIfReceived()==true)
                return;


        bool sent=false;
        int i=0;

        for(i=0; i<vecAvailableNodes.size(); i++)
        {
                if(this->vecAvailableNodes[i]->id == obj->getDestinationId() )
                {
                        sent=true;
                        obj->addToHeader(this->getId());
                        this->vecAvailableNodes[i]->receive(idSource,idDest,obj);
                        break;
                }
        }


        if (sent == false)
        {
                int idToSend = -1;
                for(int j=0; j < theTraceroute.size(); j++)
                {
                        if(theTraceroute[j].size()>0)
                        {
                                if(theTraceroute[j][0]!=idSource &&  checkIfExist(obj->getHeader(),theTraceroute[j][theTraceroute[j].size()-1])==false )
                                {
                                        idToSend = theTraceroute[j][0];
                                        for(i=0; i<vecAvailableNodes.size(); i++)
                                        {
                                                if(this->vecAvailableNodes[i]->id == idToSend)
                                                {
                                                        sent=true;
                                                        obj->addToHeader(this->getId());
                                                        this->vecAvailableNodes[i]->receive(this->id,idToSend,obj);
                                                        break;
                                                }
                                        }
                                }
                        }
                }
        }

        if (sent == false)
        {
                cout << "Sorry ,there is no way for this moment. "<<endl;
                //  cout << "The node with id: "<< idSource << " cannot send any message ";
                //cout << "to the node with the id: " << idDest <<endl;

                //
                // for(int i=1 ; i <obj->getHeader().size();i++)
                // {
                //   cout << obj->getHeader()[i] << " ==> " ;
                // }
        }

}
void Node::receive(int idSource,int idDest,ObjectRequest *obj)
{
        if(obj==NULL)
                return;
        vector<int> forResponse;

        //if it is the destination
        if(this->id == obj->getDestinationId())
        {
                cout << "I am the Node with the id : " << this->getId();
                cout << " And I received the message :  " << endl << obj->getMessage() <<endl;
                cout << "From the node with the id : " << obj->getSenderId() <<endl;
                cout << "Decrypting message ..." << endl;
                cout << "The message decrypted is : " << endl;
                string decoded = base64_decode(obj->getMessage());
                cout << decoded << endl;

                int size = obj->getHeader()[0];
                for(int i=size; i>0; i--)
                {
                        //If there is a Node that already exist so that says that I went through a false path
                        //So I have to delete all the false path
                        if(checkIfExist(forResponse, obj->getHeader()[i])==true)
                        {
                                int index=-2;
                                int indexToFind=obj->getHeader()[i];


                                if(forResponse.back()==obj->getHeader()[i])
                                {
                                        //if the false node is just next to the other false node
                                        continue;
                                }
                                else
                                {
                                        while(forResponse.size() >1 && index!=indexToFind)
                                        {
                                                forResponse.pop_back();
                                                index=forResponse.back();
                                        }
                                }
                        }
                        else
                                forResponse.push_back(obj->getHeader()[i]);
                }
                obj->receivedFlag();
                // cout << endl;
                // cout << endl << "print all false header " << endl;
                // for(int i=1 ; i <obj->getHeader().size();i++)
                // {
                //   cout << obj->getHeader()[i] << " ==> " ;
                // }
                // cout << endl <<"---------------------"<<endl;
                // for(int i=1 ; i <forResponse.size();i++)
                // {
                //   cout << forResponse[i] << " ==> " ;
                // }
                // cout << endl << "End print header " <<endl;

                sendResponse(obj->getPacketId(),obj->getDestinationId(),obj->getSenderId(),forResponse);

        }

        else
        {
                if(obj!=NULL)
                        send(idSource,idDest,obj);
        }
}

void Node::sendResponse(int idPacket,int idSource,int idDest,std::vector<int> &tracerouteBack)
{
        bool found=false;
        int i=0;
        if(this->getId()==idDest)
        {
                cout << "I am the Node with the id : " << this->getId() << " And I Received Response of the Request id : " << idPacket;
                cout << " Sent From the Node with id : " << idSource << endl;
        }

        if(tracerouteBack.size()>0)
        {

                int idToSendBack = tracerouteBack[0];
                tracerouteBack.erase (tracerouteBack.begin());
                for(i=0; i < this->getVectAvailableNodes().size(); i++)
                {
                        if(this->getVectAvailableNodes()[i]->getId()==idToSendBack)
                        {
                                found=true;
                                break;
                        }
                }
        }

        if(found==true)
                this->getVectAvailableNodes()[i]->sendResponse(idPacket,idSource,idDest,tracerouteBack);
}
