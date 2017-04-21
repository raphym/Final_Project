#ifndef ObjectRequest_H
#define ObjectRequest_H
#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <cmath>



class ObjectRequest
{
public:
ObjectRequest(std::string typeOfMessage,int packetId,int senderId,int destinationId, std::string message );
virtual ~ObjectRequest();
std::string getmessageType();
int getPacketId();
int getSenderId();
int getDestinationId();
std::string getMessage();
std::vector<int> &getHeader();
void addToHeader(int idDone);



protected:
std::string messageType;
int packetId;
int senderId;
int destinationId;
std::string message;
std::vector<int> header;

private:
};

#endif // ObjectRequest_H
