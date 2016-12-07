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
        map.getNodes()[4]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[5]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[6]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[7]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[8]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[9]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[10]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[11]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[12]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[13]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[14]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[15]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[16]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[17]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[18]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[19]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[20]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[21]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[22]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[23]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[24]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[25]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[26]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[27]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[28]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[29]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[30]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[31]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[32]->scanHotspots(map.getNodes(), map.getNumOfElements());


        TrafficLight *t2 = new TrafficLight("NewTrafiicLight", 100039,854868);

        map.addNode(t2);

        map.getNodes()[0]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[1]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[2]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[3]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[4]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[5]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[6]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[7]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[8]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[9]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[10]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[11]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[12]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[13]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[14]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[15]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[16]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[17]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[18]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[19]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[20]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[21]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[22]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[23]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[24]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[25]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[26]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[27]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[28]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[29]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[30]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[31]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[32]->scanHotspots(map.getNodes(), map.getNumOfElements());
        map.getNodes()[33]->scanHotspots(map.getNodes(), map.getNumOfElements());


        map.PrintMap();

        cout << "----------------------------------------------------------------------------------"<<endl;

        map.getNodes()[0]->send(54,0,1);
        map.getNodes()[1]->send(60,1,2);
        map.getNodes()[20]->send(65,20,21);
        map.getNodes()[17]->send(66,17,21);
        map.getNodes()[21]->send(67,21,28);
        map.getNodes()[28]->send(68,28,21);
        map.getNodes()[33]->send(70,33,20);
        cout <<endl;

        return 0;
}
