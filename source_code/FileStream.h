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
FileStream(std::string n); //constructor
virtual ~FileStream(); //destructor
int option; //option
void split(const std::string& s, char delim,std::vector<std::string>& v); //function which split a string into a vector
int LineCounters(); //return the number of lines which are in the file
int fill_ObjectsInfo_Into_Arrays(int nbLines, std::string *names,double *posX, double *posY,std::string inputFile); //function which fill the differents arrays (names, positions of x , positions of y )


protected:

private:
std::string name; //name of the file
};
#endif // FILESTREAM_H
