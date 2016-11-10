#include "Lamp.h"

using namespace std;

Lamp::Lamp(string n,double x, double y)//ctor
{
    name = new string(n);
    locationX = x;
    locationY = y;
    coverage=false;
}

Lamp::~Lamp()//dtor
{

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
