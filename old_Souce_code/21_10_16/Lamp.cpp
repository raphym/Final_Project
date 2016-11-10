#include "Lamp.h"

using namespace std;

Lamp::Lamp(string n,double x, double y , int i)//ctor
{
    name = new string(n);
    locationX = x;
    locationY = y;
    id=i;
    coverage=false;
}

Lamp::~Lamp()//dtor
{

}
int Lamp::getId()
{
    return id;
}
string Lamp::getName()
{
    return *name;
}

void Lamp::freeMemory()
{
  delete name;
}
double Lamp::getLocationX()
{
    return locationX;
}

double Lamp::getLocationY()
{
    return locationY;
}

bool Lamp::isCoverage()
{
    return coverage;
}

void Lamp::setCoverage(bool b)
{
    coverage =b;
}
