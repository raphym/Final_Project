#ifndef QUORUM_H
#define QUORUM_H
#include "Node.h"


class Quorum : public Node
{
public:
        Quorum(std::string type,std::string n,int theId,double x, double y);
        void printQuorum(std::vector<Node*> vecElementsOfTheMap);
        virtual ~Quorum();


protected:

private:
};

#endif // QUORUM_H
