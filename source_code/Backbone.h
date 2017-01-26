#ifndef BACKBONE_H
#define BACKBONE_H
#include "Node.h"


class Backbone : public Node
{
public:
        Backbone(std::string type,std::string n,int theId,double x, double y);
        void printQuorum(std::vector<Node*> vecElementsOfTheMap);
        virtual ~Backbone();


protected:

private:
};

#endif // BACKBONE_H
