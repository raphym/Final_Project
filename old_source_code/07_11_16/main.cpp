#include <vector>
#include <fstream>
#include <iostream>

#include "Lamp.h"
#include "Provider.h"
#include "TrafficLight.h"

#include "Map.h"
#include "FileStream.h"
#include <malloc.h>
using namespace std;

int main(int argc, char *argv[])
{
        Map map;

        map.getNodes()[0]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[1]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[2]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[3]->scanHotspots(map.getNodes(), map.getNumOfElements());

        map.PrintMap();
        cout << "----------------------------------------------------------------------------------"<<endl;
        cout <<endl;

        map.getNodes()[0]->send(58,0,1);
        cout <<endl;
        map.removeNode(0);
        map.getNodes()[0]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[1]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[2]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.PrintMap();
        cout << "afterRemove" << endl<<endl;
        map.getNodes()[0]->send(58,0,1);

        cout <<endl;

        return 0;
}
