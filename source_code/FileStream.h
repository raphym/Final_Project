#ifndef FILESTREAM_H
#define FILESTREAM_H
#include <string>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <vector>


class FileStream
{
public:
        FileStream(std::string n);
        virtual ~FileStream();
        int option;
        //function which split a string into a vector
        void split(const std::string& s, char delim,std::vector<std::string>& v);
        //return the number of lines which are in the file
        int LineCounters();
        //function which fill the differents arrays (names, positions of x , positions of y )
        int fill_ObjectsInfo_Into_Arrays(int nbLines, std::string *names,double *posX, double *posY,std::string inputFile);


protected:

private:
        std::string name;
};
#endif // FILESTREAM_H
