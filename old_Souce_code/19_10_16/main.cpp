#include <vector>
#include <fstream>

#include "Lamp.h"
#include "Map.h"
#include "FileStream.h"

using namespace std;

int main(int argc , char *argv[])
{
    Map map;
    map.checkCoverage();
    map.PrintMap();

    return 0;
}
