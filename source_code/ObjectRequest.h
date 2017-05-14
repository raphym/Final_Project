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
ObjectRequest(std::string typeOfMessage,std::string packetId,int senderId,int destinationId, std::string message );
virtual ~ObjectRequest();
std::string getmessageType();
std::string getPacketId();
int getSenderId();
int getDestinationId();
std::string getMessage();
std::vector<int> &getHeader();
std::vector<int> &getDirectionToExecute();
std::vector<int> &getVisitedBackbones();
std::vector<int> &getVisitedTraceroutes();
void addToHeader(int idDone);
void addToVisitedBackbones(int backboneDone);
void addToVisitedTraceroutes(int tracerouteDone);
void popFromHeader();
void popFromDirectionToExecute();
void clearDirectionToExecute();
void setMessageType(std::string messageType);



protected:
std::string messageType;
std::string packetId;
int senderId;
int destinationId;
std::string message;
std::vector<int> header;
std::vector<int> directionToExecute;
std::vector<int> visitedBackbones;
std::vector<int> visitedTraceroutes;


private:
};

#endif // ObjectRequest_H
