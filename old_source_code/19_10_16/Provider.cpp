#include "Provider.h"

using namespace std;

Provider::Provider(string n,double x, double y, int i )//ctor
{
    name = new string(n);
    locationX = x;
    locationY = y;
    id=i;
}

Provider::~Provider()//dtor
{
}

int Provider::getId()
{
    return id;
}
string Provider::getName()
{
    return *name;
}

void Provider::freeMemory()
{
  delete name;
}
double Provider::getLocationX()
{
    return locationX;
}

double Provider::getLocationY()
{
    return locationY;
}
