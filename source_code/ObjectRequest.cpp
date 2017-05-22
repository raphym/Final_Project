#include "ObjectRequest.h"

using namespace std;

ObjectRequest::ObjectRequest(string typeOfMessage,std::string packetId, int senderId,int destinationId, std::string message )   //ctor
{
        this->messageType=typeOfMessage;
        this->packetId=packetId;
        this->senderId=senderId;
        this->destinationId=destinationId;
        this->message=message;
        this->header.push_back(0);
}

ObjectRequest::~ObjectRequest() //dtor
{

}

string ObjectRequest::getmessageType()
{
        return messageType;
}

string ObjectRequest::getPacketId()
{
        return packetId;
}

std::vector<int> & ObjectRequest::getHeader()
{
        return header;
}


int ObjectRequest::getSenderId()
{
        return senderId;
}

int ObjectRequest::getDestinationId()
{
        return destinationId;
}

string ObjectRequest::getMessage()
{
        return message;
}

void ObjectRequest::addToHeader(int idDone)
{
        this->header[0]+=1;
        this->header.push_back(idDone);
}

void ObjectRequest::setMessageType(string messageType)
{
        this->messageType=messageType;
}

void ObjectRequest::popFromHeader()
{
        if(this->header.size()<=1)
                return;

        this->header[0] = this->header[0] -1;
        this->header.pop_back();
}

vector<int> &ObjectRequest::getDirectionToExecute()
{
        return directionToExecute;
}

vector<int> &ObjectRequest::getVisitedBackbones()
{
        return visitedBackbones;
}


vector<int> &ObjectRequest::getVisitedTraceroutes()
{
        return visitedTraceroutes;
}

void ObjectRequest::addToVisitedBackbones(int backboneDone)
{
        visitedBackbones.push_back(backboneDone);
}
void ObjectRequest::addToVisitedTraceroutes(int tracerouteDone)
{
        visitedTraceroutes.push_back(tracerouteDone);
}

void ObjectRequest::clearDirectionToExecute()
{
        directionToExecute.clear();
}

void ObjectRequest::popFromDirectionToExecute()
{
        directionToExecute.pop_back();
}

void ObjectRequest::clearVisitedTraceroutes()
{
        visitedTraceroutes.clear();
}
void ObjectRequest::popFromVisitedBackbones()
{
        visitedBackbones.pop_back();
}
