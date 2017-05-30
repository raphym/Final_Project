#include "FileStream.h"


using namespace std;
///////////////////////////////////////////////////////////////////////////////
//constructor
//////////////////////////////////////////////////////////////////////////////
FileStream::FileStream(string n)
{
        name=n;
}
///////////////////////////////////////////////////////////////////////////////
//destructor
//////////////////////////////////////////////////////////////////////////////
FileStream::~FileStream()
{

}
///////////////////////////////////////////////////////////////////////////////
//count the lines of the file
//////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
//function which fill the differents arrays (names, positions of x , positions of y )
//////////////////////////////////////////////////////////////////////////////
int FileStream::fill_ObjectsInfo_Into_Arrays(int nbLines,string *names, double *posX, double *posY,string inputFile)
{

        string str;
        int i=0,line=0;
        double check=0;
        ifstream file(name.c_str()); //open the file
        if ( !file )
        {
                cout << "ERROR TO OPEN THE FILE" << endl;
                return 0;
        }
        else
        {
                while(std::getline(file, str)) //each time read single line until there is not
                {
                        line++; // other line
                        vector <string> v; // a string vector
                        split(str, '\t', v); //split the line into vector v
                        if(v.size()!=3) //if there is not 3 arguments so errors
                        {
                                nbLines--;
                                cerr <<endl<< "Invalid argument in file : "<<inputFile <<" line : "  << line << '\n';
                                continue;
                        }
                        else //there is exactely 3 arguments so check them
                        {
                                try //for the locationX and locationY; its check if its is a number
                                {
                                        names[i] = v[0];

                                        check=stod(v[1]); //check the locationX
                                        posX[i]=check;


                                        check=stod(v[2]); //check the locationY
                                        posY[i]=check;

                                        i++; //increment the index for the arrays names , posX ,posY
                                }
                                catch (const std::invalid_argument& ia) //if not a number so the line is not valide go to the next line
                                {
                                        cerr <<endl<< "Invalid argument in filed : "<<inputFile <<" line : "  << line << '\n';
                                        nbLines--;
                                }
                        }
                }
        }
        file.close();
        return nbLines;
}
///////////////////////////////////////////////////////////////////////////////
//function which split a string into a vector
//////////////////////////////////////////////////////////////////////////////
void FileStream::split(const string& s, char delim,vector<string>& v)
{
        auto i = 0;
        auto pos = s.find(delim);
        while (pos != string::npos)
        {
                v.push_back(s.substr(i, pos-i));
                i = ++pos;
                pos = s.find(delim, pos);

                if (pos == string::npos)
                        v.push_back(s.substr(i, s.length()));
        }
}
