#include <vector>
#include <string>     // std::string, std::stod
#include <stdlib.h>     /* atof */
#include <cmath>
#include <stdio.h>

#include <fstream>
#include <iostream>
#include "malloc.h"

#include "Map.h"
#include "FileStream.h"
#include "string.h"

using namespace std;


Map::Map()//ctor
{
    int i=0;
    FileStream f1("/home/raphael/Documents/Graphic_Network/lamps.txt");
    nbLinesLamps = f1.LineCounters();
    if (nbLinesLamps==0)
        exit(-1);
    lamps = (Lamp*)malloc(nbLinesLamps * sizeof(Lamp));

    std::vector<std::string> names;
    names.reserve(4096*sizeof(string));

    double *posX = NULL;
    double *posY = NULL;
    posX = new double[nbLinesLamps];
    posY = new double[nbLinesLamps];

    memset(posX, '0', nbLinesLamps*sizeof(double));
    memset(posY, '0', nbLinesLamps*sizeof(double));
    f1.fillArray(nbLinesLamps,names,posX,posY);
    for(i=0; i<nbLinesLamps ;i++)
    {
        Lamp temp(names[i],posX[i],posY[i]);
        lamps[i]=temp;
    }
    delete [] posX;
    delete [] posY;

    FileStream f2("/home/raphael/Documents/Graphic_Network/providers.txt");
    nbLinesProviders = f2.LineCounters();
    if (nbLinesProviders==0)
        exit(-1);

    providers = (Provider*)malloc(nbLinesProviders * sizeof(Provider));

    names.clear();
    names.reserve(4096*sizeof(string));

    posX = new double[nbLinesLamps];
    posY = new double[nbLinesLamps];

    memset(posX, '0', nbLinesProviders*sizeof(double));
    memset(posY, '0', nbLinesProviders*sizeof(double));
    f2.fillArray(nbLinesProviders,names,posX,posY);
    for(i=0; i<nbLinesProviders ;i++)
    {
        Provider temp(names[i],posX[i],posY[i]);
        providers[i]=temp;
    }
    delete [] posX;
    delete [] posY;

}

Map::~Map()
{

  int i=0;
  for(i=0 ; i<nbLinesLamps ; i++)
  {
    lamps[i].freeMemory();
  }


  for(i=0 ; i<nbLinesProviders ; i++)
  {
    providers[i].freeMemory();
  }


  free(lamps);
  free(providers);

}

void Map::checkCoverage()
{
  int i = 0 ,j = 0 ,xProvider=0 ,yProvider=0 ,xLamp=0 , yLamp=0 ,x=0 ,y=0;

  for(i = 0 ; i< nbLinesProviders ;i++)
  {
    xProvider = providers[i].getLocationX();
    yProvider = providers[i].getLocationY();

    for(j=0 ; j<nbLinesLamps ; j++)
    {
      xLamp = lamps[j].getLocationX();
      yLamp = lamps[j].getLocationY();

      if(abs(xProvider -xLamp) <= 40  || abs(yProvider - yLamp) <=40)
        lamps[j].setCoverage(true);
    }
  }

  for(i = 0 ; i< nbLinesLamps ;i++)
  {
    for(j=i+1 ; j<nbLinesLamps ; j++)
    {
       x = abs(lamps[i].getLocationX() - lamps[j].getLocationX());
       y = abs(lamps[i].getLocationY() - lamps[j].getLocationY());

       if( ( x <=40 || y<= 40 ) && ( (lamps[i].isCoverage()==true ) || (lamps[j].isCoverage()==true ) ) )
       {
          lamps[i].setCoverage(true);
          lamps[j].setCoverage(true);
        }
    }
  }
}



void Map::printProviders()
{
    cout << "----PROVIDERS----" << endl;
    int i = 0;
    for(i=0 ; i<nbLinesProviders ; i++)
    {
      cout <<"["  <<   "Name : " << providers[i].getName() << " | Position : " << "("<<providers[i].getLocationX() << "," << providers[i].getLocationY() << ")" << "]"<< endl;
    }
}



void Map::printLamps()
{
    cout << "----LAMPS----" << endl;
    int i = 0;
    for(i=0 ; i<nbLinesLamps ; i++)
    {
      cout << "[" <<  "Name : " << lamps[i].getName() << " | Position : "<<"("<<lamps[i].getLocationX() << "," << lamps[i].getLocationY() << ")"<< " |Coverage :" << lamps[i].isCoverage() <<"]"<<endl;
    }
}


void Map::PrintMap()
{
  cout << endl << endl ;
  cout << "---------------------------------------------------------------------"<< endl ;
  cout << endl << endl ;

  cout << "**************************[MAP NETWORK]******************************"<< endl ;

  cout << endl << endl ;
  printLamps();
  cout << endl << endl ;
  printProviders();
  cout << endl << endl ;
  cout << "---------------------------------------------------------------------"<< endl ;
  cout << endl << endl ;

}
