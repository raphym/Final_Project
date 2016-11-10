#ifndef PROVIDER_H
#define PROVIDER_H
#include "Node.h"
#include <string>


class Provider : public Node
{
public:
        Provider(std::string n,double x, double y);
        virtual ~Provider();


protected:

private:

};

#endif // PROVIDER_H
