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
                outfile << "____________________\t____________________\t____________________\n";
                outfile << "-----MESSAGE_ID-----\t--------FROM--------\t---------TO---------\n";
                outfile << "____________________\t____________________\t____________________\n";

                outfile.close();
        }
        else cout << "Unable to open file";
        string packetId = getRandomId();
        ObjectRequest *obj = new ObjectRequest("info",packetId,11,46,"hello" );

        networkSend(11,46,obj);

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

Simulation::~Simulation() // dtor
{
        delete theMap;
}
