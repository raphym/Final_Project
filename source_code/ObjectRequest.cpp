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
        bool found=false;

        //find if already pass by there
        for(int i=1; i < this->header.size(); i++ )
        {
                if(this->header[i]==idDone)
                {
                        found=true;
                        break;
                }
        }

        //if there is no problem so insert it and increase the size (header[0])
        if(found==false)
        {
                this->header[0]+=1;
                this->header.push_back(idDone);
        }

        //if there is a problem change the destination id to -1 to get it out
        else if(found==true)
        {
                this->destinationId = -1;
        }
}
