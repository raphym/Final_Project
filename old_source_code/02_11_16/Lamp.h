#ifndef LAMP_H
#define LAMP_H
#include "Node.h"

class Lamp : public Node
{
    public:
      Lamp(std::string n,double x, double y , int i);
      virtual ~Lamp();


    protected:

    private:
};

#endif // LAMP_H
