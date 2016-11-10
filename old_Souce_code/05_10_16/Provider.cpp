#include "Provider.h"

using namespace std;

Provider::Provider(string n,double x, double y)//ctor
{
    name = new string(n);
    locationX = x;
    locationY = y;
}

Provider::~Provider()//dtor
{
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
