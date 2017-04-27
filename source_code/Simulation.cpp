#include "Simulation.h"

using namespace std;
static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

Simulation::Simulation(string city)
{
        string pathProviders = "input_files/" + city + "/" + "providers.txt";
        string pathLamps = "input_files/" + city + "/" + "lamps.txt";
        string pathTrafficLights = "input_files/" + city + "/" + "trafficLights.txt";

        theMap  = new Map(city, pathProviders, pathLamps, pathTrafficLights);

        theMap->refreshMap();
        theMap->quorumConstruct();

        //theMap->PrintMap();
        theMap->DFS();

        //theMap->printTraceroute();
        theMap->refreshMap();

        //cout << getRandomId() <<endl;

}

void Simulation::sendRequest()
{
        int size = theMap->getNodes().size() -1;
        theMap->refreshMap();

        for(int i=0; i< size; i++)
        {
                cout << "Node I = " << i <<endl;

                for(int j=0; j<size; j++ )
                {
                        if(i!=j)
                        {
                                cout << "Node J = " << j <<endl;
                              //  theMap->getNodes()[i]->sendRequest(i, j,"Hello World");
                        }
                }

        }
}

char Simulation::genRandom()
{

    return alphanum[rand() % stringLength];
}

string Simulation::getRandomId()
{
    srand(time(0));
    std::string Str;
    for(unsigned int i = 0; i < 20; ++i)
    {
        Str += genRandom();

    }
    return Str;
}

void Simulation::startSim()
{
  ofstream outfile;
  outfile.open("database.txt");

}

Simulation::~Simulation() // dtor
{
        delete theMap;
}
