#include "Simulation.h"

using namespace std;
Simulation::Simulation(string city)
{
        string pathProviders = "input_files/" + city + "/" +  "providers.txt";
        string pathLamps= "input_files/" + city + "/" +  "lamps.txt";
        string pathTrafficLights= "input_files/" + city + "/" +  "trafficLights.txt";

        Map map(city,pathProviders,pathLamps,pathTrafficLights);

        map.refreshMap();
        map.PrintMap();

        map.getNodes()[0]->send(58, 0, 1);

        cout <<endl;
}

Simulation::~Simulation() //dtor
{

}
