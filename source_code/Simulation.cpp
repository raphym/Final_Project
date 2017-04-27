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

void Simulation::sendRequest()
{
        int size = theMap->getNodes().size() -1;
        theMap->refreshMap();

        for(int i=0; i< size; i++)
        {
                cout << "Node I = " << i <<endl;

                for(int j=0; j<size; j++ )
                {
                        if(i!=j)
                        {
                                cout << "Node J = " << j <<endl;
                                //  theMap->getNodes()[i]->sendRequest(i, j,"Hello World");
                        }
                }

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

void Simulation::startSim()
{
        ofstream outfile;
        outfile.open("database.txt");
        if (outfile.is_open())
        {
                outfile << "MessageId From To\n";
                outfile.close();
        }
        else cout << "Unable to open file";
        string packetId = getRandomId();
        ObjectRequest *obj = new ObjectRequest("info",packetId,0,5,"hello" );

        networkSend(0,5,obj);

}

void Simulation::networkSend(int idSource,int idDest,ObjectRequest *obj)
{
        int index =-1;


        while(obj->getmessageType()!="ACK" || obj->getmessageType()!="NAK")
        {
                if(obj->getHeader()[0]==0)
                        index=idSource;
                else
                        index = obj->getHeader()[0];

                //cout << "From " << index << " To " << 6 <<endl;
                obj =  theMap->getNodes()[index]->send(obj);
                if(obj->getHeader()[0]==0)
                  break;
        }
}

Simulation::~Simulation() // dtor
{
        delete theMap;
}
