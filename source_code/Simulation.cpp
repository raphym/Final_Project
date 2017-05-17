#include "Simulation.h"

using namespace std;

Simulation::Simulation(string city)
{
        this->nbSuccess=0;
        this->nbFailures=0;
        this->nbRequests=0;
        string pathProviders = "input_files/" + city + "/" + "providers.txt";
        string pathLamps = "input_files/" + city + "/" + "lamps.txt";
        string pathTrafficLights = "input_files/" + city + "/" + "trafficLights.txt";

        theMap  = new Map(city, pathProviders, pathLamps, pathTrafficLights);
        theMap->refreshMap();
        theMap->quorumConstruct();
        theMap->refreshMap();
        theMap->constructAllTraceroute();
        theMap->refreshMap();



        //for debug
        //theMap->printListOfQuorum();
        //theMap->PrintMap();
        //theMap->printTraceroute();

}

void Simulation::startSim()
{
        sendRequests();
}

void Simulation::sendRequests()
{
        //
        // int k=1;
        // int idSource;
        // int idDest;
        // string message;
        // string line;
        //
        // //For test
        // float temps;
        // clock_t t1, t2;
        // t1 = clock();
        //
        // ifstream myfile ("input_files/Events-Schedule/Schedule.txt");
        // if (myfile.is_open())
        // {
        //         while ( getline (myfile,line) )
        //         {
        //                 vector<string> request;
        //                 split(line,'\t',request);
        //
        //                 //details of the request
        //                 idSource = stoi(request[0]);
        //                 idDest = stoi(request[1]);
        //                 message = request[2];
        //                 string packetId = getRandomId(20,k);
        //                 k++;
        //                 string encodedMessage = base64_encode(reinterpret_cast<const unsigned char*>(message.c_str()), message.length());
        //                 ObjectRequest *obj = new ObjectRequest("INFO",packetId,idSource,idDest,encodedMessage);
        //                 //send the request
        //                 this->nbRequests++;
        //                 networkSend(idSource,idDest,obj);
        //                 delete obj;
        //         }
        //         myfile.close();
        //
        //         t2 = clock();
        //         temps = (float)(t2-t1)/CLOCKS_PER_SEC;
        //         cout <<endl<<"Statistic:" <<endl;
        //         cout <<"-----------------------------------" <<endl;
        //         cout <<"number of Requests : " << this->nbRequests <<endl;
        //         cout <<"number of Success : " << this->nbSuccess <<endl;
        //         cout <<"number of Failures : " << this->nbFailures <<endl;
        //
        //         double percentsOfFailures =0;
        //         if(this->nbRequests >0 )
        //                 percentsOfFailures = (this->nbFailures / this->nbRequests)*(100);
        //
        //         cout << "Percentage of failures : " <<percentsOfFailures<<" %"<<endl;
        //         cout << "TIME IN SECOND  : "<<temps<<endl;
        //         cout <<"-----------------------------------" <<endl;
        // }
        // else cout << "Unable to open file";




        //For test
        float temps;
        clock_t t1, t2;
        t1 = clock();
        sendRequestsTest();
        t2 = clock();
        temps = (float)(t2-t1)/CLOCKS_PER_SEC;
        //temps = temps/1000;//to sec

        cout <<endl<<"Statistic:" <<endl;
        cout <<"-----------------------------------" <<endl;
        cout <<"number of Requests : " << this->nbRequests <<endl;
        cout <<"number of Success : " << this->nbSuccess <<endl;
        cout <<"number of Failures : " << this->nbFailures <<endl;

        double percentsOfFailures =0;
        if(this->nbRequests >0 )
                percentsOfFailures = (this->nbFailures / this->nbRequests)*(100);

        cout << "Percentage of failures : " <<percentsOfFailures<<" %"<<endl;
        cout << "TIME IN SECOND  : "<<temps<<endl;
        cout <<"-----------------------------------" <<endl;

}

void Simulation::sendRequestsTest()
{
        int k=1;
        for(int i=0; i < theMap->getNodes().size(); i++)
        {
                for(int j=0; j < theMap->getNodes().size(); j++)
                {
                        if(i!=j && i!=10 && j!=10) //&& i!=10 && j!=10 && j!=32 && j!=14 &&  j!=41 && j!=47
                        {
                                this->nbRequests++;
                                string packetId = getRandomId(20,k);
                                k++;
                                ObjectRequest *obj = new ObjectRequest("INFO",packetId,i,j,"hello");
                                //send the request
                                networkSend(i,j,obj);
                                delete obj;
                        }
                }
        }
}

void Simulation::networkSend(int idSource,int idDest,ObjectRequest *obj)
{
        int index =-1;
        bool begin=false;
        while(index!=idDest)
        {

                //If there is no direction found
                if(obj->getmessageType()=="NAK")
                {
                        cout << "NAK RECEIVE : "<<idSource<<" CANNOT SENT MESSAGE TO "<<idDest <<endl;
                        this->nbFailures++;
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
                this->nbSuccess++;
                //cout << "ACK RECEIVE : "<<idSource<<" SENT MESSAGE TO "<<idDest <<endl;
        }
}


string Simulation::getRandomId(int len, int i)
{
        srand (i);
        //srand(time(0));
        string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        string newstr;
        int pos;
        while(newstr.size() != len) {
                pos = ((rand() % (str.size() - 1)));
                newstr += str.substr(pos,1);
        }
        return newstr;
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
