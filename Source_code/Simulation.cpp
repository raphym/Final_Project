#include "Simulation.h"

using namespace std;
Simulation::Simulation()
{

        Map map ("Tel-Aviv","providers.txt","lamps.txt","trafficLights.txt");

        map.getNodes()[0]->scanHotspots(map.getNodes());
        map.getNodes()[1]->scanHotspots(map.getNodes());
        map.getNodes()[2]->scanHotspots(map.getNodes());
        map.getNodes()[3]->scanHotspots(map.getNodes());

        map.PrintMap();
        cout << "----------------------------------------------------------------------------------"<<endl;
        cout <<endl;

        map.getNodes()[1]->send(58,1,0);
        cout <<endl;
        map.removeNode(0);
        map.getNodes()[0]->scanHotspots(map.getNodes());
        map.getNodes()[1]->scanHotspots(map.getNodes());
        map.getNodes()[2]->scanHotspots(map.getNodes());

        map.PrintMap();
        cout << "afterRemove" << endl<<endl;
        map.getNodes()[1]->send(58,1,0);

        cout <<endl;
}

Simulation::~Simulation() //dtor
{

}
