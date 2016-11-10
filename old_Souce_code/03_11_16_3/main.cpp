#include <vector>
#include <fstream>
#include <iostream>

#include "Lamp.h"
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

        map.PrintMap();
        return 0;
}
