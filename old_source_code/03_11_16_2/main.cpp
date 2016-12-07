#include <vector>
#include <fstream>
#include <iostream>

#include "Lamp.h"
#include "Map.h"
#include "FileStream.h"
#include <malloc.h>
using namespace std;

int main(int argc , char *argv[])
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

    map.PrintMap();
    return 0;
}
