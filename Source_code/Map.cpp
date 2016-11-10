#include "Map.h"
using namespace std;

Map::Map() //ctor
{
        nbOfElements=0;
        loadMap();
}

Map::~Map()
{
        int i=0;

        for(i=0; i<nbOfElements; i++)
        {
                delete vecElementsOfTheMap[i];
        }
}


Lamp** Map::loadLamps()
{
        int i=0;
        //f is a FileStream Object to read informations about the lamps
        FileStream f("lamps.txt");
        nbLamps = f.LineCounters();
        if (nbLamps==0)
                exit(-1);
        Lamp **lamps = new Lamp*[nbLamps];

        string *names=NULL;
        double *posX = NULL;
        double *posY = NULL;

        names = new string[nbLamps];
        posX = new double[nbLamps];
        posY = new double[nbLamps];

        f.fill_ObjectsInfo_Into_Arrays(nbLamps,names,posX,posY);
        for(i=0; i<nbLamps; i++)
        {
                lamps[i] = new Lamp(names[i],posX[i],posY[i]);
                nbOfElements++;
        }
        delete [] posX;
        delete [] posY;
        delete [] names;

        return lamps;
}

Provider** Map::loadProviders()
{
        int i=0;
        string *names=NULL;
        double *posX = NULL;
        double *posY = NULL;


        //f is a FileStream Object to read informations about the providers
        FileStream f("providers.txt");
        nbProviders = f.LineCounters();
        if (nbProviders==0)
                exit(-1);
        Provider **providers = new Provider*[nbProviders];

        names = new string[nbProviders];
        posX = new double[nbProviders];
        posY = new double[nbProviders];

        f.fill_ObjectsInfo_Into_Arrays(nbProviders,names,posX,posY);
        for(i=0; i<nbProviders; i++)
        {
                providers[i] = new Provider(names[i],posX[i],posY[i]);
                nbOfElements++;
        }
        delete [] posX;
        delete [] posY;
        delete [] names;

        return providers;
}

TrafficLight** Map::loadTrafficLights()
{
        int i=0;
        string *names=NULL;
        double *posX = NULL;
        double *posY = NULL;

        //f is a FileStream Object to read informations about the trafficLights
        FileStream f("trafficLights.txt");
        nbTrafficLight = f.LineCounters();
        if (nbTrafficLight==0)
                exit(-1);
        TrafficLight **trafficLights = new TrafficLight*[nbTrafficLight];

        names = new string[nbTrafficLight];
        posX = new double[nbTrafficLight];
        posY = new double[nbTrafficLight];


        f.fill_ObjectsInfo_Into_Arrays(nbTrafficLight,names,posX,posY);
        for(i=0; i<nbTrafficLight; i++)
        {
                trafficLights[i] = new TrafficLight(names[i],posX[i],posY[i]);
                nbOfElements++;
        }
        delete [] posX;
        delete [] posY;
        delete [] names;

        return trafficLights;
}

void Map::loadMap()
{
        int i,j;

        //regroupper tous les elements:
        Lamp **lamps= loadLamps();
        Provider **providers=loadProviders();
        TrafficLight **trafficLights=loadTrafficLights();

        i=j=0;
        for(i=0; i<nbLamps; i++)
        {
                vecElementsOfTheMap.push_back(lamps[i]);
                j++;
        }

        for(i=0; i<nbProviders; i++)
        {
                vecElementsOfTheMap.push_back(providers[i]);
                j++;
        }

        for(i=0; i<nbTrafficLight; i++)
        {
                vecElementsOfTheMap.push_back(trafficLights[i]);
                j++;
        }

        delete [] lamps;
        delete [] providers;
        delete [] trafficLights;
}

void Map::addNode(Node *n)
{
        if(n==NULL)
                return;

        vecElementsOfTheMap.push_back(n);
}



void Map::removeNode(int id)
{
        for(int i=0; i < vecElementsOfTheMap.size(); i++)
        {
                if(vecElementsOfTheMap[i]->getId() == id)
                        vecElementsOfTheMap[i]->erase();
        }

}

vector<Node*> Map::getNodes()
{
        return vecElementsOfTheMap;
}


int Map::getNumOfElements()
{
        return nbOfElements;
}


void Map::PrintMap()
{
        for(int i=0; i< vecElementsOfTheMap.size(); i++ )
        {
                if(vecElementsOfTheMap[i]->checkIfErased()==true)
                        continue;
                cout << "---------------------------------------------------"<<endl;
                cout << "ID : " << vecElementsOfTheMap[i]->getId() <<" | Name : " << vecElementsOfTheMap[i]->getName() << " | Position : "<<"("<<vecElementsOfTheMap[i]->getLocationX() << "," << vecElementsOfTheMap[i]->getLocationY() << ")" <<endl;
                cout << "available Nodes : " << endl;
                vecElementsOfTheMap[i]->printAvailableNodes();
        }
}
