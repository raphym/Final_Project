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
    loadMap();
}

Map::~Map()
{

  int i=0;
  for(i=0 ; i<nbLinesLamps ; i++)
  {
    delete lamps[i];
  }

  for(i=0 ; i<nbLinesProviders ; i++)
  {
    delete providers[i];
  }

  delete [] lamps;
  delete [] providers;
}

void Map::loadMap()
{

    int i=0;
    //f1 is a FileStream Object to read informations about the lamps
    FileStream f1("lamps.txt",LAMP);
    nbLinesLamps = f1.LineCounters();
    if (nbLinesLamps==0)
        exit(-1);
    lamps = new Lamp*[nbLinesLamps];

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
        lamps[i] = new Lamp(names[i],posX[i],posY[i],identification[i]);
    }
    delete [] posX;
    delete [] posY;
    delete [] identification;


    //f2 is a FileStream Object to read informations about the providers
    FileStream f2("providers.txt",PROVIDER);
    nbLinesProviders = f2.LineCounters();
    if (nbLinesProviders==0)
        exit(-1);

    providers = new Provider*[nbLinesProviders];

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
      providers[i] = new Provider(names[i],posX[i],posY[i],identification[i]);
    }
    delete [] posX;
    delete [] posY;
    delete [] identification;
}

Lamp** Map::getLamps()
{
  return lamps;
}


void Map::printProviders()
{
    cout << "----PROVIDERS----" << endl;
    int i = 0;
    for(i=0 ; i<nbLinesProviders ; i++)
    {
      cout <<"["  << "ID : " << providers[i]->getId() << " | Name : " << providers[i]->getName() << " | Position : " << "("<<providers[i]->getLocationX() << "," << providers[i]->getLocationY() << ")" << "]"<< endl;
    }
}



void Map::printLamps()
{
    cout << "----LAMPS----" << endl;
    int i = 0;
    for(i=0 ; i<nbLinesLamps ; i++)
    {
      cout << "---------------------------------------------------"<<endl;
      cout << "[" << endl;
      cout << "ID : " << lamps[i]->getId() <<" | Name : " << lamps[i]->getName() << " | Position : "<<"("<<lamps[i]->getLocationX() << "," << lamps[i]->getLocationY() << ")" <<endl;
      cout << "available Nodes : " << endl;
      lamps[i]->printAvailableNodes();
      cout << "]" << endl <<endl;
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

 int Map::getNumLamps()
 {
   return nbLinesLamps;
 }



/*
PAS BESOIN (si control from Map)
void Map::NodeScan(int i)
{
  lamps[i]->scanHotspots((Node**)lamps, nbLinesLamps);
}

*/
