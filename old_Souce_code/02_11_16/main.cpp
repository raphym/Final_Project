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
    map.getLamps()[1]->scanHotspots((Node**)map.getLamps(), map.getNumLamps());
    map.getLamps()[0]->scanHotspots((Node**)map.getLamps(), map.getNumLamps());
    map.getLamps()[2]->scanHotspots((Node**)map.getLamps(), map.getNumLamps());
    map.getLamps()[3]->scanHotspots((Node**)map.getLamps(), map.getNumLamps());
    map.getLamps()[0]->scanHotspots((Node**)map.getLamps(), map.getNumLamps());
    map.printLamps();

    cout << "////////////////"<< endl;
    cout << map.getLamps()[3]->getVectAvailableNodes()[1]->getName() << endl;
    cout << map.getLamps()[3]->getNbAvailableNodes()<< endl;






    /*
    map.NodeScan(0);
    map.NodeScan(1);
    map.NodeScan(2);
    map.NodeScan(3);
    map.printLamps();
    map.printProviders();
    */

    /*
    Node n1("a",10,10,0);

    map.getLamps()[0].alloc();
    map.getLamps()[0].voisins[0]=&n1;


    cout << map.getLamps()[0].voisins[0]->getName()<<endl;
    n1.freeMemory();
    map.getLamps()[0].dealloc();
    */
    //map.PrintMap();
    // Node n1("a",10,10,0);
    // Node n2("b",11,11,1);
    //
    // n1.freeMemory();
    // n2.freeMemory();

/*
    Node n3("c",12,12,2);
    Node n4("d",13,13,3);
    Node n5("e",14,14,4);
    Node n6("f",15,15,5);


    n1.voisins.push_back(&n2);
    n1.voisins.push_back(&n3);
    n1.voisins.push_back(&n4);
    n1.voisins.push_back(&n5);
    n1.voisins.push_back(&n6);

    cout << n1.voisins[0]->getName()<<endl;
    cout << n1.voisins[1]->getName()<<endl;
    cout << n1.voisins[2]->getName()<<endl;
    cout << n1.voisins[3]->getName()<<endl;
    cout << n1.voisins[4]->getName()<<endl;

    n1.freeMemory();
    n2.freeMemory();

    n3.freeMemory();
    n4.freeMemory();
    n5.freeMemory();
    n6.freeMemory();

*/
    return 0;
}
