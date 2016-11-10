#ifndef FILESTREAM_H
#define FILESTREAM_H
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>


class FileStream
{
public:
        FileStream(std::string n);
        virtual ~FileStream();
        int option;
        int LineCounters(); //count how many object there are
        void fill_ObjectsInfo_Into_Arrays(int nbLines, std::string *names,double *posX, double *posY);


protected:

private:
        std::string name;
};
#endif // FILESTREAM_H
