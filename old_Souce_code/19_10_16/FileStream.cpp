#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "FileStream.h"


using namespace std;

FileStream::FileStream(string n,int opt)
{
    name=n;
    option=opt;
}

FileStream::~FileStream()
{

}


int FileStream::LineCounters()
{
    int lines = 0;
    string str;
    ifstream file(name.c_str());
    if ( !file )
    {
        cout << "ERROR TO OPEN THE FILE" << endl;
        return 0;
    }
    else
    {
        while(std::getline(file, str))
        {
            ++lines;
        }
    }
    file.close();
    return lines;
}


void FileStream::fill_ObjectsInfo_Into_Arrays(int nbLines ,std::vector<std::string> &names, double *posX , double *posY,int *identification)
{
    string str;
    string str2;

    int i=0;
    ifstream file(name.c_str());
    if ( !file )
    {
        cout << "ERROR TO OPEN THE FILE" << endl;
        exit(-1);
    }

    for( i=0 ; i<nbLines ;i++)
    {
      file >> identification[i];
      file >> str2;
      file >> posX[i];
      file >> posY[i];
      std::getline(file, str);
      names.push_back(str2);
    }
    file.close();
}
