#include "Simulation.h"

using namespace std;
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

        theMap->getNodes()[22]->sendRequest(22, 8,"hello");



}

void Simulation::sendRequest()
{
        //cout << "HERE " << theMap->getNodes().size() << endl;
}



Simulation::~Simulation() // dtor
{
        delete theMap;
}
