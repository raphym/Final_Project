#include "FileStream.h"


using namespace std;

FileStream::FileStream(string n)
{
        name=n;
}

FileStream::~FileStream()
{

}

//return the number of lines which are in the file
int FileStream::LineCounters()
{
        int lines = 0;
        string str;
        ifstream file(name.c_str()); //open the file
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

//function which fill the differents arrays (names, positions of x , positions of y )
int FileStream::fill_ObjectsInfo_Into_Arrays(int nbLines,string *names, double *posX, double *posY,string inputFile)
{
        string str2;
        int i=0;
        int j=1;
        double k=0;
        ifstream file(name.c_str()); //open the file
        if ( !file )
        {
                cout << "ERROR TO OPEN THE FILE" << endl;
                exit(-1);
        }

        for( i=0; i<nbLines; i++,j++)
        {
                file >> names[i]; //name of the object
                try //for the locationX ; its check if it is a number
                {
                        file >> str2;
                        k=stod(str2);
                }
                catch (const std::invalid_argument& ia) //if not a number so the line is not valide go to the next line
                {
                        std::cerr <<endl<< "Invalid argument in file : "<<inputFile <<" line : "  << j << '\n';
                        i--;
                        nbLines--;
                        std::getline(file, str2);
                        continue;
                }
                posX[i]=k;
                try //for the locationY ; its check if it is a number
                {
                        file >> str2;
                        k=stod(str2);
                }
                catch (const std::invalid_argument& ia) //if not a number so the line is not valide go to the next line
                {
                        std::cerr <<endl<< "Invalid argument in file : "<<inputFile <<" line : "  << j << '\n';
                        i--;
                        nbLines--;
                        std::getline(file, str2);
                        continue;
                }
                posY[i]=k;
                std::getline(file, str2);
        }
        file.close();

        return nbLines; //return the num of the lines to know if there was invalid lines
}
