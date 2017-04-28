#include "Simulation.h"

using namespace std;
static const char alphanum[] =
        "0123456789"
        "!@#$%^&*"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

Simulation::Simulation(string city)
{
        string pathProviders = "input_files/" + city + "/" + "providers.txt";
        string pathLamps = "input_files/" + city + "/" + "lamps.txt";
        string pathTrafficLights = "input_files/" + city + "/" + "trafficLights.txt";

        theMap  = new Map(city, pathProviders, pathLamps, pathTrafficLights);

        theMap->refreshMap();
        theMap->quorumConstruct();

        //theMap->PrintMap();
        theMap->DFS();

        //theMap->printTraceroute();
        theMap->refreshMap();

        //cout << getRandomId() <<endl;

}

void Simulation::startSim()
{
        ofstream outfile;
        outfile.open("output_files/database.txt");
        if (outfile.is_open())
        {
                outfile << "____________________\t____________________\t____________________\n";
                outfile << "-----MESSAGE_ID-----\t--------FROM--------\t---------TO---------\n";
                outfile << "____________________\t____________________\t____________________\n";

                outfile.close();
        }
        else cout << "Unable to open file";
        sendRequests();
}

void Simulation::sendRequests()
{
        string packetId;
        int idSource;
        int idDest;
        string message;

        string line;
        ifstream myfile ("input_files/Events-Schedule/Schedule.txt");
        if (myfile.is_open())
        {
                while ( getline (myfile,line) )
                {
                        vector<string> request;
                        split(line,'\t',request);

                        //details of the request
                        idSource = stoi(request[0]);
                        idDest = stoi(request[1]);
                        message = request[2];
                        packetId = getRandomId();
                        string encodedMessage = base64_encode(reinterpret_cast<const unsigned char*>(message.c_str()), message.length());
                        ObjectRequest *obj = new ObjectRequest("info",packetId,idSource,idDest,encodedMessage);
                        //send the request
                        networkSend(idSource,idDest,obj);
                        delete obj;
                }
                myfile.close();
        }
        else cout << "Unable to open file";
}

void Simulation::networkSend(int idSource,int idDest,ObjectRequest *obj)
{
        int index =-1;
        bool begin=false;

        while(index!=idDest)
        {
                //If there is no direction found
                if(obj->getHeader()[0]==0 && obj->getmessageType()=="NAK")
                {
                        cout << "NAK RECEIVE : "<<idSource<<" CANNOT SENT MESSAGE TO "<<idDest <<endl;
                        break;
                }

                //First sending
                if(obj->getHeader()[0]==0 && begin==false)
                {
                        index=idSource;
                        obj->addToHeader(index);
                }
                //Other sending
                else
                {
                        index = obj->getHeader()[obj->getHeader()[0]];
                }

                //cout << "From " << index <<endl;
                theMap->refreshMap();
                begin=true;
                obj =  theMap->getNodes()[index]->send(obj);
        }

        if(index==idDest)
        {
                cout << "ACK RECEIVE : "<<idSource<<" SENT MESSAGE TO "<<idDest <<endl;
        }
}

char Simulation::genRandom()
{

        return alphanum[rand() % stringLength];
}

string Simulation::getRandomId()
{
        srand(time(0));
        std::string Str;
        for(unsigned int i = 0; i < 20; ++i)
        {
                Str += genRandom();

        }
        return Str;
}
//function which split a string into a vector
void Simulation::split(string& s, char delim,vector<string>& v)
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
Simulation::~Simulation() // dtor
{
        delete theMap;
}
