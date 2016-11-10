#include "Map.h"
using namespace std;

Map::Map() //ctor
{
        loadMap();
}

Map::~Map()
{
        for(int i=0; i<vecElementsOfTheMap.size(); i++)
                delete vecElementsOfTheMap[i];
}


vector<Lamp*> Map::loadLamps()
{
        int i=0;
        //f is a FileStream Object to read informations about the lamps
        FileStream f("lamps.txt");
        int nbLamps = f.LineCounters();
        if (nbLamps==0)
                exit(-1);

        vector<Lamp*> lamps;

        string *names=NULL;
        double *posX = NULL;
        double *posY = NULL;

        names = new string[nbLamps];
        posX = new double[nbLamps];
        posY = new double[nbLamps];

        f.fill_ObjectsInfo_Into_Arrays(nbLamps,names,posX,posY);
        for(i=0; i<nbLamps; i++)
                lamps.push_back(new Lamp(names[i],posX[i],posY[i]));
        delete [] posX;
        delete [] posY;
        delete [] names;

        return lamps;
}


vector<Provider*> Map::loadProviders()
{
        int i=0;
        string *names=NULL;
        double *posX = NULL;
        double *posY = NULL;


        //f is a FileStream Object to read informations about the providers
        FileStream f("providers.txt");
        int nbProviders = f.LineCounters();
        if (nbProviders==0)
                exit(-1);
        vector<Provider*> providers;

        names = new string[nbProviders];
        posX = new double[nbProviders];
        posY = new double[nbProviders];

        f.fill_ObjectsInfo_Into_Arrays(nbProviders,names,posX,posY);
        for(i=0; i<nbProviders; i++)
                providers.push_back(new Provider(names[i],posX[i],posY[i]));
        delete [] posX;
        delete [] posY;
        delete [] names;

        return providers;
}

vector<TrafficLight*> Map::loadTrafficLights()
{
        int i=0;
        string *names=NULL;
        double *posX = NULL;
        double *posY = NULL;

        //f is a FileStream Object to read informations about the trafficLights
        FileStream f("trafficLights.txt");
        int nbTrafficLight = f.LineCounters();
        if (nbTrafficLight==0)
                exit(-1);
        vector<TrafficLight*> trafficLights;

        names = new string[nbTrafficLight];
        posX = new double[nbTrafficLight];
        posY = new double[nbTrafficLight];


        f.fill_ObjectsInfo_Into_Arrays(nbTrafficLight,names,posX,posY);
        for(i=0; i<nbTrafficLight; i++)
                trafficLights.push_back(new TrafficLight(names[i],posX[i],posY[i]));
        delete [] posX;
        delete [] posY;
        delete [] names;

        return trafficLights;
}

void Map::loadMap()
{
        //regroupper tous les elements:
        vector<Lamp*> lamps= loadLamps();
        vector<Provider*>providers=loadProviders();
        vector<TrafficLight*>trafficLights=loadTrafficLights();

        for(int i=0; i<lamps.size(); i++)
                vecElementsOfTheMap.push_back(lamps[i]);

        for(int i=0; i<providers.size(); i++)
                vecElementsOfTheMap.push_back(providers[i]);

        for(int i=0; i<trafficLights.size(); i++)
                vecElementsOfTheMap.push_back(trafficLights[i]);
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
