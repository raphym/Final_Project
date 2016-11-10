#ifndef FILESTREAM_H
#define FILESTREAM_H
#include <string>
#include <vector>

class FileStream
{
    public:
        FileStream(std::string n);
        virtual ~FileStream();
        int LineCounters();
        void fillArray(int nbLines , std::vector<std::string> &names,double *posX , double *posY);


    protected:

    private:
      std::string name;
};
#endif // FILESTREAM_H
