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
        theMap->refreshMap();

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
                                theMap->getNodes()[i]->sendRequest(i, j,"Hello World");
                        }
                }

        }
}



Simulation::~Simulation() // dtor
{
        delete theMap;
}
