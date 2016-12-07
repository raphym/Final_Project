#ifndef FILESTREAM_H
#define FILESTREAM_H
#include <string>
#define LAMP 1
#define PROVIDER 2
#define LIST_EVENT 3

class FileStream
{
public:
        FileStream(std::string n,int opt);
        virtual ~FileStream();
        int option;
        int LineCounters();
        void fill_ObjectsInfo_Into_Arrays(int nbLines, std::string *names,double *posX, double *posY);


protected:

private:
        std::string name;
};
#endif // FILESTREAM_H
