//#include <iostream>

#include <QApplication>
#include <QPushButton>
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


    QApplication app(argc,argv);
    QPushButton button("salut");
    button.show();
    return app.exec();

    return 0;

}
