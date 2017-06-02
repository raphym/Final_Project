#include "Simulation.h"

using namespace std;
///////////////////////////////////////////////////////////////////////////////
//constructor
//////////////////////////////////////////////////////////////////////////////
Simulation::Simulation(string city,int max_hop)
{
        this->nbSuccess=0;
        this->nbFailures=0;
        this->nbRequests=0;
        this->softwareHop=0;
        this->hardwareHop=0;
        this->loaded=false;

        string pathProviders = "input_files/" + city + "/" + "providers.txt";
        string pathLamps = "input_files/" + city + "/" + "lamps.txt";
        string pathTrafficLights = "input_files/" + city + "/" + "trafficLights.txt";

        theMap  = new Map(city, pathProviders, pathLamps, pathTrafficLights,max_hop);

        //load the map and check if it is loaded
        int load = theMap->loadMap();
        if(load!=-1)
        {
                theMap->refreshMap();
                theMap->quorumConstruct();
                theMap->refreshMap();
                theMap->constructAllTraceroute();
                theMap->refreshMap();
                this->loaded=true;

                //to write in files about the map
                theMap->writeMap();
                theMap->writeQuorums();
                theMap->writeTraceroutes();
                return;
        }
        else
        {
                this->loaded=false;
                return;
        }
}
///////////////////////////////////////////////////////////////////////////////
//start the Simulation
//////////////////////////////////////////////////////////////////////////////
void Simulation::startSim(int choice)
{
        int flag =0;
        if(choice==0)
                flag = sendRequestsTest();
        else if(choice==1)
                flag = sendRequests();
        else
                return;

        if(flag==0)
        {
                //-----now we calcul the statistics

                //for the softwareHop hops
                int nums = searchMaxInVector(vecOfSoftwareHop) +1;
                int *analysisGraphVecOfSoftwareHop = constructAnalysisGraph(vecOfSoftwareHop,nums);
                writeDataGraph(analysisGraphVecOfSoftwareHop,nums,"Graph of software hops");

                //for the hardware hops
                nums = searchMaxInVector(vecOfHardwareHop) +1;
                int *analysisGraphVecOfHardwareHop = constructAnalysisGraph(vecOfHardwareHop,nums);
                writeDataGraph(analysisGraphVecOfHardwareHop,nums,"Graph of hardware hops");

                //free the memory from the graph
                delete [] analysisGraphVecOfSoftwareHop;
                delete [] analysisGraphVecOfHardwareHop;
        }
        else
                return;

}
///////////////////////////////////////////////////////////////////////////////
//send Requests according to the Events-Schedule
//////////////////////////////////////////////////////////////////////////////
int Simulation::sendRequests()
{

        int k=1;
        int idSource;
        int idDest;
        string message;
        string line;
        theMap->refreshMap();

        float temps;
        clock_t t1, t2;
        t1 = clock();

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
                        string packetId = getRandomId(20,k);
                        k++;
                        string encodedMessage = base64_encode(reinterpret_cast<const unsigned char*>(message.c_str()), message.length());
                        ObjectRequest *obj = new ObjectRequest("INFO",packetId,idSource,idDest,encodedMessage);
                        //send the request
                        this->nbRequests++;
                        networkSend(idSource,idDest,obj);
                        delete obj;
                        //init hop
                        softwareHop=0;
                        hardwareHop=0;
                }
                myfile.close();

                //for the Statistic
                t2 = clock();
                temps = (float)(t2-t1)/CLOCKS_PER_SEC;
                ofstream outfile;
                outfile.open("output_files/Statistic.txt"); //std::ios_base::app
                if (outfile.is_open())
                {
                        outfile << endl<<"Statistic:" <<endl;
                        outfile << "-----------------------------------" <<endl;
                        outfile << "number of Requests : " << this->nbRequests <<endl;
                        outfile << "number of Success : " << this->nbSuccess <<endl;
                        outfile << "number of Failures : " << this->nbFailures <<endl;
                        double percentsOfFailures =0;
                        if(this->nbRequests >0 )
                                percentsOfFailures = (this->nbFailures / this->nbRequests)*(100);

                        outfile << "Percentage of failures : " <<percentsOfFailures<<" %"<<endl;
                        outfile << "TIME IN SECOND  : "<<temps<<endl;
                        outfile <<"-----------------------------------" <<endl;
                        outfile.close();
                }
                else
                {
                        cout << "Unable to open Statistic"<<endl;
                        return -1;
                }
        }
        else
        {
                cout << "Unable to open Events-Schedule, your file is corrupted"<<endl;
                return -1;
        }
        return 0;
}
///////////////////////////////////////////////////////////////////////////////
//send Requests n*n TEST Queries
//////////////////////////////////////////////////////////////////////////////
int Simulation::sendRequestsTest()
{

        float temps;
        clock_t t1, t2;
        t1 = clock();
        //Start the sending

        int k=1;
        for(int i=0; i < theMap->getNodes().size(); i++)
        {
                for(int j=0; j < theMap->getNodes().size(); j++)
                {
                        if(i!=j && i!=10 && j!=10 && j!=32 && j!=14 &&  j!=41 && j!=47 ) //&& i!=10 && j!=10 && j!=32 && j!=14 &&  j!=41 && j!=47
                        {
                                this->nbRequests++;
                                string packetId = getRandomId(20,k);
                                k++;
                                ObjectRequest *obj = new ObjectRequest("INFO",packetId,i,j,"hello");
                                //send the request
                                networkSend(i,j,obj);
                                delete obj;
                                //init hop
                                softwareHop=0;
                                hardwareHop=0;
                        }
                }
        }

        //End
        t2 = clock();
        temps = (float)(t2-t1)/CLOCKS_PER_SEC;
        //temps = temps/1000;//to sec
        //for the Statistic
        t2 = clock();
        temps = (float)(t2-t1)/CLOCKS_PER_SEC;
        ofstream outfile;
        outfile.open("output_files/Statistic.txt"); //std::ios_base::app
        if (outfile.is_open())
        {
                outfile << endl<<"Statistic:" <<endl;
                outfile << "-----------------------------------" <<endl;
                outfile << "number of Requests : " << this->nbRequests <<endl;
                outfile << "number of Success : " << this->nbSuccess <<endl;
                outfile << "number of Failures : " << this->nbFailures <<endl;
                double percentsOfFailures =0;
                if(this->nbRequests >0 )
                        percentsOfFailures = (this->nbFailures / this->nbRequests)*(100);

                outfile << "Percentage of failures : " <<percentsOfFailures<<" %"<<endl;
                outfile << "TIME IN SECOND  : "<<temps<<endl;
                outfile <<"-----------------------------------" <<endl;
                outfile.close();
        }
        else
        {
                cout << "Unable to open Statistic"<<endl;
                return -1;
        }
        return 0;
}
///////////////////////////////////////////////////////////////////////////////
//the network send , this function mimics the wifi sending
//////////////////////////////////////////////////////////////////////////////
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
                        softwareHop++;
                        hardwareHop++;
                }
                //Other sending
                else
                {
                        index = obj->getHeader()[obj->getHeader()[0]];
                        if(obj->getmessageType()!="INFO")
                        {
                                hardwareHop++;
                                if(theMap->getNodes()[index]->isItBackbone() && index!=idDest && begin==true)
                                        softwareHop++;
                        }

                }

                //cout << "From " << index <<endl;
                theMap->refreshMap();
                begin=true;
                obj =  theMap->getNodes()[index]->send(obj);
        }

        if(index==idDest)
        {
                this->nbSuccess++;
                softwareHop++;
                //cout << "ACK RECEIVE : "<<idSource<<" SENT MESSAGE TO "<<idDest <<endl;
        }

        //cout << endl<<"softwareHop : " << softwareHop <<endl;
        vecOfSoftwareHop.push_back(softwareHop);
        vecOfHardwareHop.push_back(hardwareHop);
}
///////////////////////////////////////////////////////////////////////////////
//get a Random Id for a packet
//////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
//function which split a string into a vector
//////////////////////////////////////////////////////////////////////////////
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
///////////////////////////////////////////////////////////////////////////////
//function which print a Vector
//////////////////////////////////////////////////////////////////////////////
void Simulation::printVector(string vectorName, vector<int> vec)
{
        cout <<endl;
        cout << "Printing " << vectorName<<endl;
        for(int i=0; i< vec.size(); i++)
        {
                cout << vec[i] << "==>";
        }
        cout <<endl;
}
///////////////////////////////////////////////////////////////////////////////
//function which print an array
//////////////////////////////////////////////////////////////////////////////
void Simulation::printArray(std::string vectorName, int* arr,int nums)
{
        cout <<endl;
        cout << "-----------------------------";
        cout <<endl;
        cout << "Printing " << vectorName<<endl;
        for(int i=0; i< nums; i++)
        {
                cout << arr[i] << "==>";
        }
        cout <<endl;
        cout << "-----------------------------";
        cout <<endl;
}
///////////////////////////////////////////////////////////////////////////////
//function which search the max in a vector
//////////////////////////////////////////////////////////////////////////////
int Simulation::searchMaxInVector(std::vector<int>v)
{
        int max = v[0];
        for(int i =0; i< v.size(); i++ )
        {
                if(v[i]>max)
                        max=v[i];
        }

        return max;
        //cout << "max : " << max<<endl;
}
///////////////////////////////////////////////////////////////////////////////
//construct Analysis Graph
//////////////////////////////////////////////////////////////////////////////
int* Simulation::constructAnalysisGraph(std::vector<int>v,int nums)
{

        int *graph = new int[nums];

        //init the y axis
        for(int i=0; i < nums; i++)
        {
                graph[i]=0;
        }
        //run on the v and update the array
        for(int i=0; i <v.size(); i++)
        {
                graph[v[i]]++;
        }
        return graph;
}
///////////////////////////////////////////////////////////////////////////////
//write Data Graph
//////////////////////////////////////////////////////////////////////////////
void Simulation::writeDataGraph(int *analysisGraph,int nums,string name)
{
        ofstream outfile;
        string path = "output_files/";
        path+=name;
        path+=".txt";
        outfile.open(path); //std::ios_base::app
        if (outfile.is_open())
        {
                outfile << "---------------------------------------------------";
                outfile << endl << name << endl;
                for(int i=0; i <nums; i++)
                        outfile << i << "\t" << analysisGraph[i] <<endl;
                outfile.close();
        }
        else cout << "Unable to open file";
}
///////////////////////////////////////////////////////////////////////////////
//get the bool loaded to know if the map has been loaded
//////////////////////////////////////////////////////////////////////////////
bool Simulation::getLoaded()
{
        return loaded;
}
///////////////////////////////////////////////////////////////////////////////
//Destructor
//////////////////////////////////////////////////////////////////////////////
Simulation::~Simulation() // dtor
{
        if(theMap!=NULL)
                delete theMap;
}
