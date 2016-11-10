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
#define DISTANCE 40

Map::Map()//ctor
{
    int i=0;
    //f1 is a FileStream Object to read informations about the lamps
    FileStream f1("lamps.txt",LAMP);
    nbLinesLamps = f1.LineCounters();
    if (nbLinesLamps==0)
        exit(-1);
    lamps = (Lamp*)malloc(nbLinesLamps * sizeof(Lamp));

    std::vector<std::string> names;
    names.reserve(4096*sizeof(string));

    double *posX = NULL;
    double *posY = NULL;
    int *identification=NULL;

    posX = new double[nbLinesLamps];
    posY = new double[nbLinesLamps];
    identification=new int[nbLinesLamps];

    memset(posX, '0', nbLinesLamps*sizeof(double));
    memset(posY, '0', nbLinesLamps*sizeof(double));
    memset(identification, '0', nbLinesLamps*sizeof(int));

    f1.fill_ObjectsInfo_Into_Arrays(nbLinesLamps,names,posX,posY,identification);
    for(i=0; i<nbLinesLamps ;i++)
    {
        Lamp temp(names[i],posX[i],posY[i],identification[i]);
        lamps[i]=temp;
    }
    delete [] posX;
    delete [] posY;
    delete [] identification;
    //f2 is a FileStream Object to read informations about the providers
    FileStream f2("providers.txt",PROVIDER);
    nbLinesProviders = f2.LineCounters();
    if (nbLinesProviders==0)
        exit(-1);

    providers = (Provider*)malloc(nbLinesProviders * sizeof(Provider));

    names.clear();
    names.reserve(4096*sizeof(string));

    posX = new double[nbLinesProviders];
    posY = new double[nbLinesProviders];
    identification=new int[nbLinesProviders];

    memset(posX, '0', nbLinesProviders*sizeof(double));
    memset(posY, '0', nbLinesProviders*sizeof(double));
    memset(identification, '0', nbLinesProviders*sizeof(int));

    f2.fill_ObjectsInfo_Into_Arrays(nbLinesProviders,names,posX,posY,identification);
    for(i=0; i<nbLinesProviders ;i++)
    {
        Provider temp(names[i],posX[i],posY[i],identification[i]);
        providers[i]=temp;
    }
    delete [] posX;
    delete [] posY;
    delete [] identification;
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

      if(abs(xProvider -xLamp) <= DISTANCE  || abs(yProvider - yLamp) <= DISTANCE)
        lamps[j].setCoverage(true);
    }
  }

  for(i = 0 ; i< nbLinesLamps ;i++)
  {
    for(j=i+1 ; j<nbLinesLamps ; j++)
    {
       x = abs(lamps[i].getLocationX() - lamps[j].getLocationX());
       y = abs(lamps[i].getLocationY() - lamps[j].getLocationY());

       if( ( x <=DISTANCE || y<= DISTANCE ) && ( (lamps[i].isCoverage()==true ) || (lamps[j].isCoverage()==true ) ) )
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
      cout <<"["  << "ID : " << providers[i].getId() << " | Name : " << providers[i].getName() << " | Position : " << "("<<providers[i].getLocationX() << "," << providers[i].getLocationY() << ")" << "]"<< endl;
    }
}



void Map::printLamps()
{
    cout << "----LAMPS----" << endl;
    int i = 0;
    for(i=0 ; i<nbLinesLamps ; i++)
    {
      cout << "[" << "ID : " << lamps[i].getId() <<" | Name : " << lamps[i].getName() << " | Position : "<<"("<<lamps[i].getLocationX() << "," << lamps[i].getLocationY() << ")"<< " |Coverage :" << lamps[i].isCoverage() <<"]"<<endl;
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
