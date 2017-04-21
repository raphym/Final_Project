#include "ObjectRequest.h"

using namespace std;

ObjectRequest::ObjectRequest(int packetId, int senderId,int destinationId, std::string message )   //ctor
{

        this->packetId=packetId;
        this->senderId=senderId;
        this->destinationId=destinationId;
        this->message=message;
        this->header.push_back(0);
}

ObjectRequest::~ObjectRequest() //dtor
{

}

int ObjectRequest::getPacketId()
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
