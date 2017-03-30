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
ObjectRequest(int packetId,int senderId,int destinationId, std::string message );
virtual ~ObjectRequest();
int getPacketId();
int getSenderId();
int getDestinationId();
std::string getMessage();
std::vector<int> &getHeader();
void addToHeader(int idDone);
bool checkIfReceived();

protected:
int packetId;
int senderId;
int destinationId;
std::string message;
std::vector<int> header;
bool received;

private:
};

#endif // ObjectRequest_H
