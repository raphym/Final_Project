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
ObjectRequest(std::string typeOfMessage,std::string packetId,int senderId,int destinationId, std::string message ); //constructor
virtual ~ObjectRequest(); //destructor
std::string getmessageType(); //get the message Type
std::string getPacketId(); //get the PacketId
int getSenderId(); //get the SenderId
int getDestinationId(); //get the DestinationId
std::string getMessage(); //get the message
std::vector<int> &getHeader(); //get the Header of the object request
std::vector<int> &getDirectionToExecute(); //get the Direction To Execute
std::vector<int> &getVisitedBackbones(); //return the visited backbones
std::vector<int> &getVisitedTraceroutes(); //return the Visited Traceroutes
void addToHeader(int idDone); //Add To the Header
void addToVisitedBackbones(int backboneDone); //add to the vector VisitedBackbones
void addToVisitedTraceroutes(int tracerouteDone); //add to the vector VisitedTraceroutes
void popFromHeader(); //pop From the Header
void popFromDirectionToExecute(); //pop From DirectionToExecute
void clearDirectionToExecute(); //clear the vector directionToExecute
void setMessageType(std::string messageType); //set the MessageType
void clearVisitedTraceroutes(); //clear the vector VisitedTraceroutes
void popFromVisitedBackbones(); //pop From VisitedBackbones
int getCounterBackbone(); // get the counter value of backbone that have been traversed
void incrementCounterBackbone(); //increment the counter value of backbone that have been traversed
void decrementCounterBackBone(); //decrement the counter value of backbone that have been traversed

protected:
std::string messageType; // the type of the message
std::string packetId; // the id of the packet
int senderId; //the id of the sender node
int destinationId; //the id of the destination node
std::string message; //the message
std::vector<int> header; //the header
std::vector<int> directionToExecute; //the direction to execute
std::vector<int> visitedBackbones; //the vector of visited backbones
std::vector<int> visitedTraceroutes; //the vector of visited traceroutes
int counterBackbone; //this value is a counter of backbone that have been traversed

private:
};

#endif // ObjectRequest_H
