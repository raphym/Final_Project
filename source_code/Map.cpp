#include "Map.h"
using namespace std;
///////////////////////////////////////////////////////////////////////////////
//constructor
//////////////////////////////////////////////////////////////////////////////
Map::Map(string name,string fileProviders, string fileLamps, string fileTrafficLights,int max_hop,int idStartConstructQuorum)   //ctor
{
        this->name=name;
        this->fileProviders=fileProviders;
        this->fileLamps=fileLamps;
        this->fileTrafficLights=fileTrafficLights;
        this->pbInLoading=false;
        this->max_hop=max_hop;
        this->idStartConstructQuorum=idStartConstructQuorum;
        this->maxTracerouteLength=9;
}
///////////////////////////////////////////////////////////////////////////////
//Destructor
//////////////////////////////////////////////////////////////////////////////
Map::~Map()
{
        for(int i=0; i<vecElementsOfTheMap.size(); i++)
        {
                if(vecElementsOfTheMap[i]!=NULL)
                        delete vecElementsOfTheMap[i];
        }
}
///////////////////////////////////////////////////////////////////////////////
//load the lamp return a vector of lamps
//////////////////////////////////////////////////////////////////////////////
vector<Node*> Map::loadLamps()
{
        int i=0;
        //f is a FileStream Object to read informations about the lamps
        FileStream f(this->fileLamps);
        int nbLamps = f.LineCounters();
        if (nbLamps==0)
        {
                cout << "your file : " << this->fileLamps << " is corrupted"<< endl;
                this->pbInLoading=true;
                vector<Node*> lamps;
                return lamps;
        }
        vector<Node*> lamps;
        lamps.reserve(nbLamps*sizeof(Node*));

        string *names = new string[nbLamps];
        double *posX = new double[nbLamps];
        double *posY = new double[nbLamps];

        nbLamps = f.fill_ObjectsInfo_Into_Arrays(nbLamps,names,posX,posY,this->fileLamps);
        if(nbLamps==0)
        {
                delete [] posX;
                delete [] posY;
                delete [] names;
                cout << "your file : " << this->fileLamps << " is corrupted"<< endl;
                exit(-1);
        }


        for(i=0; i<nbLamps; i++)
                lamps.push_back(new Node("LAMP",names[i],New_Node_Id,posX[i],posY[i],max_hop));
        delete [] posX;
        delete [] posY;
        delete [] names;

        return lamps;
}
///////////////////////////////////////////////////////////////////////////////
//load the providers return a vector of providers
//////////////////////////////////////////////////////////////////////////////
vector<Node*> Map::loadProviders()
{
        int i=0;

        //f is a FileStream Object to read informations about the providers
        FileStream f(this->fileProviders);
        int nbProviders = f.LineCounters();
        if (nbProviders==0)
        {
                cout << "your file : " << this->fileProviders << " is corrupted"<< endl;
                vector<Node*> providers;
                this->pbInLoading=true;
                return providers;
        }
        vector<Node*> providers;
        providers.reserve(nbProviders * sizeof(Node*));
        string *names = new string[nbProviders];
        double *posX = new double[nbProviders];
        double *posY = new double[nbProviders];
        nbProviders = f.fill_ObjectsInfo_Into_Arrays(nbProviders,names,posX,posY,this->fileProviders);
        if(nbProviders==0)
        {
                delete [] posX;
                delete [] posY;
                delete [] names;
                cout << "your file : " << this->fileProviders << " is corrupted"<< endl;
                exit(-1);
        }
        for(i=0; i<nbProviders; i++)
                providers.push_back(new Node("PROVIDER",names[i],New_Node_Id,posX[i],posY[i],max_hop));
        delete [] posX;
        delete [] posY;
        delete [] names;

        return providers;
}
///////////////////////////////////////////////////////////////////////////////
//load the trafficLights return a vector of trafficLights
//////////////////////////////////////////////////////////////////////////////
vector<Node*> Map::loadTrafficLights()
{
        int i=0;
        //f is a FileStream Object to read informations about the trafficLights
        FileStream f(this->fileTrafficLights);
        int nbTrafficLight = f.LineCounters();
        if (nbTrafficLight==0)
        {
                cout << "your file : " << this->fileTrafficLights << " is corrupted"<< endl;
                vector<Node*> trafficLights;
                this->pbInLoading=true;
                return trafficLights;
        }

        vector<Node*> trafficLights;
        trafficLights.reserve(nbTrafficLight * sizeof(Node*));

        string *names = new string[nbTrafficLight];
        double *posX = new double[nbTrafficLight];
        double *posY = new double[nbTrafficLight];
        nbTrafficLight = f.fill_ObjectsInfo_Into_Arrays(nbTrafficLight,names,posX,posY,this->fileTrafficLights);
        if(nbTrafficLight==0)
        {
                delete [] posX;
                delete [] posY;
                delete [] names;
                cout << "your file : " << this->fileTrafficLights << " is corrupted"<< endl;
                exit(-1);
        }
        for(i=0; i<nbTrafficLight; i++)
                trafficLights.push_back(new Node("TRAFFIC_LIGHT",names[i],New_Node_Id,posX[i],posY[i],max_hop));
        delete [] posX;
        delete [] posY;
        delete [] names;

        return trafficLights;
}
///////////////////////////////////////////////////////////////////////////////
//load the map with the lamps , providers and trafficlights
//////////////////////////////////////////////////////////////////////////////
int Map::loadMap()
{
        //regroupper tous les elements:
        vector<Node*> lamps= loadLamps();
        vector<Node*>providers=loadProviders();
        vector<Node*>trafficLights=loadTrafficLights();

        int numsOfElements = lamps.size()+ providers.size() + trafficLights.size();
        if(this->pbInLoading==true || (numsOfElements-1) < this->idStartConstructQuorum)
        {
                if((numsOfElements-1) < this->idStartConstructQuorum)
                {
                        cout << "The id from start to construct the quorum is not valid (x >  numbers of elements)"<<endl;
                }
                //free the memory and return -1
                int i=0;
                for(i=0; i< lamps.size(); i++)
                {
                        if(lamps[i]!=NULL)
                                delete lamps[i];
                }
                for(i=0; i< providers.size(); i++)
                {
                        if(providers[i]!=NULL)
                                delete providers[i];
                }
                for(i=0; i< trafficLights.size(); i++)
                {
                        if(trafficLights[i]!=NULL)
                                delete trafficLights[i];
                }
                return -1;
        }

        size_t size = lamps.size()*sizeof(Node*);
        size+= providers.size()*sizeof(Node*);
        size+= trafficLights.size()*sizeof(Node*);

        vecElementsOfTheMap.reserve(size);

        for(int i=0; i<lamps.size(); i++)
                vecElementsOfTheMap.push_back(lamps[i]);

        for(int i=0; i<providers.size(); i++)
                vecElementsOfTheMap.push_back(providers[i]);

        for(int i=0; i<trafficLights.size(); i++)
                vecElementsOfTheMap.push_back(trafficLights[i]);

        return 0;
}
///////////////////////////////////////////////////////////////////////////////
//Add a node to the Map
//////////////////////////////////////////////////////////////////////////////
void Map::addNode(Node *n)
{
        if(n==NULL)
                return;
        vecElementsOfTheMap.push_back(n);
}
///////////////////////////////////////////////////////////////////////////////
//remove a node from the Map
//////////////////////////////////////////////////////////////////////////////
void Map::removeNode(int id)
{
        for(int i=0; i < vecElementsOfTheMap.size(); i++)
        {
                if(vecElementsOfTheMap[i]->getId() == id)
                        vecElementsOfTheMap[i]->erase();
        }

}
///////////////////////////////////////////////////////////////////////////////
// return a vectors of all elements of the map (nodes)
//////////////////////////////////////////////////////////////////////////////
vector<Node*> Map::getNodes()
{
        return vecElementsOfTheMap;
}
///////////////////////////////////////////////////////////////////////////////
// print the map
//////////////////////////////////////////////////////////////////////////////
void Map::PrintMap()
{
        cout << endl << "Name of the Map : " << this->name << endl;
        for(int i=0; i< vecElementsOfTheMap.size(); i++ )
        {
                if(vecElementsOfTheMap[i]->checkIfErased()==true)
                        continue;
                cout << "_____________"<<endl<<endl;
                cout << "TYPE: " << vecElementsOfTheMap[i]->getType() << " | ID : " << vecElementsOfTheMap[i]->getId() <<" | Name : " << vecElementsOfTheMap[i]->getName() << " | Position : "<<"("<<vecElementsOfTheMap[i]->getLocationX() << "," << vecElementsOfTheMap[i]->getLocationY() << ")" <<endl;
                cout << "available Nodes : " << endl;
                vecElementsOfTheMap[i]->printAvailableNodes();

                if(vecElementsOfTheMap[i]->getType()=="Backbone")
                {
                        Backbone *b = (Backbone*)vecElementsOfTheMap[i];
                        b->printQuorum(vecElementsOfTheMap);
                }
                if(vecElementsOfTheMap[i]->getType()!="Backbone" && vecElementsOfTheMap[i]->getlistOfQuorum().size()>0)
                {
                        cout << "Linked to Backbone :" << endl;
                        Node *currentNode =vecElementsOfTheMap[i];
                        for(int j = 0; j< currentNode->getlistOfQuorum().size(); j++)
                        {
                                cout << vecElementsOfTheMap[currentNode->getlistOfQuorum()[j]]->getName() << " ";
                        }
                        cout << endl;
                }
        }
}
///////////////////////////////////////////////////////////////////////////////
//Refresh the scan hotspots of each node in the map
//////////////////////////////////////////////////////////////////////////////
void Map::refreshMap()
{
        Node *currentNode = NULL;
        for(int i=0; i<vecElementsOfTheMap.size(); i++)
        {
                currentNode   = vecElementsOfTheMap[i];
                currentNode->scanHotspots(vecElementsOfTheMap,currentNode->getVectAvailableNodes());
        }
}
///////////////////////////////////////////////////////////////////////////////
//clear the map of deleted elements
//////////////////////////////////////////////////////////////////////////////
void Map::Garbage_Collector()
{
        for(int i=0; i< vecElementsOfTheMap.size(); i++)
        {
                if(vecElementsOfTheMap[i]->checkIfErased()==true)
                {
                        delete vecElementsOfTheMap[i];
                        vecElementsOfTheMap.erase(vecElementsOfTheMap.begin()+i);
                }
        }
}
///////////////////////////////////////////////////////////////////////////////
//Function which running BFS on a single Node
//////////////////////////////////////////////////////////////////////////////
vector<Node*> Map::runBFS(Node *currentNode)
{
        //cout << currentNode->getName() << endl; // rajout pour test print the quorums
        int choiceId = currentNode->getId();
        int pullQueue =1;
        int nums = vecElementsOfTheMap.size();
        string *bfsArrayColor = new string[nums];
        int *bfsArrayDistance = new int [nums];
        int *bfsArrayPiId = new int [nums];

        for(int i=0; i<nums; i++)
        {
                bfsArrayColor[i] = "WHITE";
                bfsArrayDistance[i] = -1;
                bfsArrayPiId[i] = -1;
        }

        bfsArrayColor[choiceId] = "GREY";
        bfsArrayDistance[choiceId] = 0;
        bfsArrayPiId[choiceId] = -1;

        queue<Node*> myqueue;
        myqueue.push(currentNode);

        int pointerId = -1;

        if(currentNode->getVisited()==0)
                currentNode->setVisited(INCREMENT);
        while(!myqueue.empty() && pullQueue <= MAX_BFS)
        {

                pullQueue++;
                Node *pointer=myqueue.front();
                myqueue.pop();


                vector<Node*> neighbors = pointer->getVectAvailableNodes();
                pointerId = pointer->getId();

                //cout << "test "<< pointerId << endl;
                for(int i =0; i< neighbors.size(); i++ )
                {
                        int neighborsId=neighbors[i]->getId();
                        if(bfsArrayColor[neighborsId]=="WHITE" && vecElementsOfTheMap[neighborsId]->getVisited()<2)
                        {
                                currentNode->setToBeBackbone();
                                currentNode->addTolistOfQuorum(neighborsId);
                                //vecElementsOfTheMap[neighborsId]->addTolistOfQuorum(currentNode->getId());//reciprocate
                                bfsArrayColor[neighborsId]="GREY";
                                bfsArrayDistance[neighborsId]=bfsArrayDistance[pointerId]+1;
                                bfsArrayPiId[neighborsId]= pointerId;
                                myqueue.push(neighbors[i]);
                                if(neighbors[i]->getVisited()==0)
                                        neighbors[i]->setVisited(INCREMENT);
                        }
                }
                bfsArrayColor[pointerId]="BLACK";
                vecElementsOfTheMap[pointerId]->setVisited(INCREMENT);
        }

        //if the numbers of pullQueue >= maxBFS so before quit the function
        //save the nodes that discovers but not yet checked theirs neighbors
        vector<Node*> remainderNodes;
        while(!myqueue.empty())
        {
                remainderNodes.push_back(myqueue.front());
                myqueue.pop();
        }

        delete [] bfsArrayColor;
        delete [] bfsArrayDistance;
        delete [] bfsArrayPiId;

        return remainderNodes;
}
///////////////////////////////////////////////////////////////////////////////
//reset the visited indication (if 0 white , 1 grey , 2 black)
//////////////////////////////////////////////////////////////////////////////
void Map::resetVisited()
{
        for(int i=0; i < vecElementsOfTheMap.size(); i++)
                vecElementsOfTheMap[i]->setVisited(RESET);
}
///////////////////////////////////////////////////////////////////////////////
//Function which construct the quorums it's running the function runBFS
//////////////////////////////////////////////////////////////////////////////
void Map::quorumConstruct()
{
        // For BFS
        resetVisited();
        int currentId = this->idStartConstructQuorum;
        vector<Node *> remainderNodes;
        vector<Node *> bfsNodes;
        Node *pointer = NULL;
        bfsNodes.push_back(vecElementsOfTheMap[currentId]);

        while (!bfsNodes.empty())
        {
                pointer = bfsNodes.front();
                bfsNodes.erase(bfsNodes.begin());

                if (pointer->getVisited() < 2)
                {
                        //run bfs and receive the remaining nodes
                        remainderNodes = runBFS(pointer);
                        //copy the remaining node into the queue bfsNodes
                        for (int i = 0; i < remainderNodes.size(); i++)
                        {
                                int id = remainderNodes[i]->getId();
                                if (check(bfsNodes, id) == false)
                                {
                                        bfsNodes.push_back(remainderNodes[i]);
                                }
                        }
                }
        }

        //check which of the nodes are qurorum
        int sizeOfVecElementsOfTheMap = vecElementsOfTheMap.size();
        for(int i=0; i<sizeOfVecElementsOfTheMap; i++)
        {
                if(vecElementsOfTheMap[i]->isItBackbone()==true)
                {
                        Node *current = vecElementsOfTheMap[i];
                        string name = current->getName();
                        double posX = current->getLocationX();
                        double posY = current->getLocationY();
                        int oldId= current->getId();
                        int sizeOfQuorum = current->getlistOfQuorum().size();

                        Backbone *b = new Backbone("Backbone",name,oldId,posX,posY,max_hop);
                        b->setToBeBackbone();
                        for(int k=0; k< sizeOfQuorum; k++)
                                b->addTolistOfQuorum(current->getlistOfQuorum()[k]);

                        vecElementsOfTheMap[i]=b;
                        delete current;
                }
        }
        refreshMap();
}
///////////////////////////////////////////////////////////////////////////////
//Function which //print the quorums
//////////////////////////////////////////////////////////////////////////////
void Map::printListOfQuorum()
{
        for(int i=0; i<vecElementsOfTheMap.size(); i++)
        {
                if(vecElementsOfTheMap[i]->isItBackbone())
                {
                        cout << endl;
                        cout << "Backbone Name : " << vecElementsOfTheMap[i]->getName();
                        cout << ", contains : ";
                        int size = vecElementsOfTheMap[i]->getlistOfQuorum().size();
                        for(int j=0; j< size; j++)
                        {
                                int id = vecElementsOfTheMap[i]->getlistOfQuorum()[j];
                                cout << " " <<  vecElementsOfTheMap[id]->getName();
                        }
                        cout << endl;
                }
        }
}
///////////////////////////////////////////////////////////////////////////////
//check if a specific Node exists in a vector
//////////////////////////////////////////////////////////////////////////////
bool Map::check(vector<Node *> bfsNodes, int id)
{
        for (int i = 0; i < bfsNodes.size(); i++)
        {
                if (bfsNodes[i]->getId() == id)
                        return true;
        }
        return false;
}
///////////////////////////////////////////////////////////////////////////////
//check if a specific Node id exists in a vector
//////////////////////////////////////////////////////////////////////////////
bool Map::check(vector<int> bfsNodes, int id)
{
        for (int i = 0; i < bfsNodes.size(); i++)
        {
                if (bfsNodes[i] == id)
                        return true;
        }
        return false;
}
///////////////////////////////////////////////////////////////////////////////
//Construct the traceroutes for the nodes of the graph
//////////////////////////////////////////////////////////////////////////////
void Map::constructAllTraceroute()
{
        int numsOfNodes = vecElementsOfTheMap.size();
        for(int i=0; i < numsOfNodes; i++)
        {
                constructTraceroute(vecElementsOfTheMap[i]->getId());
        }
}
///////////////////////////////////////////////////////////////////////////////
//Construct a traceroute for a specific node
//////////////////////////////////////////////////////////////////////////////
void Map::constructTraceroute(int idSource)
{
        int idOrigin = idSource;
        // Mark all the vertices as not visited
        int numsOfNodes=vecElementsOfTheMap.size();
        bool *visited = new bool[numsOfNodes];

        // Create an array to store paths
        int *path = new int[numsOfNodes];
        int path_index = 0; // Initialize path[] as empty

        // Initialize all vertices as not visited
        for (int i = 0; i < numsOfNodes; i++)
                visited[i] = false;

        // Call the recursive helper function to print all paths
        recursiveDFS(idSource,idOrigin, visited, path, path_index);

        delete [] visited;
        delete [] path;
}
///////////////////////////////////////////////////////////////////////////////
//run DFS recursive to construct a traceroute
//////////////////////////////////////////////////////////////////////////////
void Map::recursiveDFS(int idSource,int idOrigin, bool visited[],int path[], int &path_index)
{
        // Mark the current node and store it in path[]
        visited[idSource] = true;
        path[path_index] = idSource;
        path_index++;

        // If current vertex is a backbone and it is not the origin so create a vect of traceroute
        // current path[]
        if( (vecElementsOfTheMap[idSource]->isItBackbone()) && (idSource!=idOrigin) )
        {
                vector<int>*traceroute = new std::vector<int>();

                //save the traceroute only if the size is not bigger than a max
                if(path_index < this->maxTracerouteLength)
                {
                        for (int i = 1; i<path_index; i++)
                        {
                                traceroute->push_back(path[i]);
                        }
                        //add the vect of traceroute to the traceroute of the origin node
                        vecElementsOfTheMap[idOrigin]->getTheTraceroute().push_back(*traceroute);
                        delete traceroute;
                }
        }

        else // If current vertex is not a backbone
        {
                // Recur for all the vertices adjacent to current vertex
                vector<Node*> neighbors = vecElementsOfTheMap[idSource]->getVectAvailableNodes();
                for(int i=0; i<neighbors.size(); i++)
                {
                        if(!visited[neighbors[i]->getId()])
                                recursiveDFS(neighbors[i]->getId(),idOrigin, visited, path, path_index);
                }
        }

        // Remove current vertex from path[] and mark it as unvisited
        path_index--;
        visited[idSource] = false;
}
///////////////////////////////////////////////////////////////////////////////
//print the Traceroute of each node
//////////////////////////////////////////////////////////////////////////////
void Map::printTraceroute()
{

        cout << endl << "Print of TraceRoute for each node" << endl << endl;

        for(int i=0; i<vecElementsOfTheMap.size(); i++)
        {
                vecElementsOfTheMap[i]->printTraceroute();
        }

        cout << "END of print TraceRoute" << endl<< endl;
}
///////////////////////////////////////////////////////////////////////////////
//write the Map in a file
//////////////////////////////////////////////////////////////////////////////
void Map::writeMap()
{
        vector<string> ve;
        ve.push_back("\n");
        ve.push_back("Name of the Map : " + this->name + "\n");
        string temp ="";
        for(int i=0; i< vecElementsOfTheMap.size(); i++ )
        {
                temp ="";
                if(vecElementsOfTheMap[i]->checkIfErased()==true)
                        continue;
                temp += "_____________";
                temp += "\n\n";
                temp += "TYPE: ";
                temp += vecElementsOfTheMap[i]->getType();
                temp += " | ID : ";
                temp +=  to_string(vecElementsOfTheMap[i]->getId());
                temp += " | Name : ";
                temp += vecElementsOfTheMap[i]->getName();
                temp += " | Position : ";
                temp += "(";
                temp +=  to_string_with_precision(vecElementsOfTheMap[i]->getLocationX(),6);
                temp += ",";
                temp +=  to_string_with_precision(vecElementsOfTheMap[i]->getLocationY(),6);
                temp += ")";
                temp += "\n";
                temp += "available Nodes : ";

                if(vecElementsOfTheMap[i]->getVectAvailableNodes().size()==0)
                        temp += "[]";
                temp += "\n";
                for(int j=0; j<vecElementsOfTheMap[i]->getVectAvailableNodes().size(); j++)
                {
                        if (j==0 && j == vecElementsOfTheMap[i]->getVectAvailableNodes().size()-1)
                        {
                                temp += "[";
                                temp += vecElementsOfTheMap[i]->getVectAvailableNodes()[0]->getName();
                                temp += "]";
                                temp += "\n";
                        }

                        else if (j==0)
                        {
                                temp += "[";
                                temp += vecElementsOfTheMap[i]->getVectAvailableNodes()[0]->getName();
                                temp += ",";
                        }

                        else if (j==vecElementsOfTheMap[i]->getVectAvailableNodes().size() -1 )
                        {
                                temp += vecElementsOfTheMap[i]->getVectAvailableNodes()[j]->getName();
                                temp += "]";
                                temp += "\n";
                        }

                        else
                        {
                                temp += vecElementsOfTheMap[i]->getVectAvailableNodes()[j]->getName();
                                temp += ",";
                        }
                }

                if(vecElementsOfTheMap[i]->getType()=="Backbone")
                {
                        Backbone *b = (Backbone*)vecElementsOfTheMap[i];

                        int size = b->getlistOfQuorum().size();
                        string name = "Quorum of Backbone " + vecElementsOfTheMap[i]->getName();
                        temp += "\n";
                        temp += name;
                        temp += ", contains : ";
                        for(int j=0; j< size; j++)
                        {
                                int id = b->getlistOfQuorum()[j];
                                temp += " ";
                                temp += vecElementsOfTheMap[id]->getName();
                        }
                        temp += "\n";
                }
                ve.push_back(temp);
        }


        ofstream outfile;
        string path = "output_files/";
        path+="Map";
        path+=".txt";
        outfile.open(path); //std::ios_base::app
        if (outfile.is_open())
        {
                for(int i=0; i<ve.size(); i++)
                        outfile << ve[i];
        }
        else cout << "Unable to write the Map data";
}
///////////////////////////////////////////////////////////////////////////////
//write the Quorums in a file
//////////////////////////////////////////////////////////////////////////////
void Map::writeQuorums()
{
        vector<string> ve;
        ve.push_back("\n");
        ve.push_back("Quorums of the Map : " + this->name + "\n");
        string temp="";
        for(int i=0; i<vecElementsOfTheMap.size(); i++)
        {
                temp="";
                if(vecElementsOfTheMap[i]->isItBackbone())
                {
                        temp +="\n";
                        temp +="Backbone Name : ";
                        temp +=vecElementsOfTheMap[i]->getName();
                        temp +=", contains : ";
                        int size = vecElementsOfTheMap[i]->getlistOfQuorum().size();
                        for(int j=0; j< size; j++)
                        {
                                int id = vecElementsOfTheMap[i]->getlistOfQuorum()[j];
                                temp +=" ";
                                temp +=vecElementsOfTheMap[id]->getName();
                        }
                        temp +="\n";
                }
                ve.push_back(temp);
        }

        ofstream outfile;
        string path = "output_files/";
        path+="Quorums";
        path+=".txt";
        outfile.open(path); //std::ios_base::app
        if (outfile.is_open())
        {
                for(int i=0; i<ve.size(); i++)
                        outfile << ve[i];
        }
        else cout << "Unable to write the Quorums data";
}
///////////////////////////////////////////////////////////////////////////////
//write the Traceroutes in a file
//////////////////////////////////////////////////////////////////////////////
void Map::writeTraceroutes()
{
        vector<string> ve;
        ve.push_back("\n");
        ve.push_back("TraceRoute for each node of the Map : " + this->name + "\n\n");
        string temp="";

        for(int k=0; k<vecElementsOfTheMap.size(); k++)
        {
                temp="";
                for(int i=0; i< vecElementsOfTheMap[k]->getTheTraceroute().size(); i++)
                {
                        temp +="List of ";
                        temp += vecElementsOfTheMap[k]->getName();
                        temp += " : ";
                        temp += "\n";

                        for(int j=0; j< vecElementsOfTheMap[k]->getTheTraceroute()[i].size(); j++)
                        {
                                temp += "{ ID : ";
                                temp += to_string(vecElementsOfTheMap[k]->getTheTraceroute()[i][j]);
                                temp += " , Name : ";
                                int theId=vecElementsOfTheMap[k]->getTheTraceroute()[i][j];
                                temp += vecElementsOfTheMap[theId]->getName();
                                temp += " }";
                                temp += "\n";
                        }
                        temp += "\n";
                }
                temp += "\n";
                ve.push_back(temp);
        }

        ofstream outfile;
        string path = "output_files/";
        path+="Traceroutes";
        path+=".txt";
        outfile.open(path); //std::ios_base::app
        if (outfile.is_open())
        {
                for(int i=0; i<ve.size(); i++)
                        outfile << ve[i];
        }
        else cout << "Unable to write the Traceroutes data";

}
///////////////////////////////////////////////////////////////////////////////
//to string with precision
//////////////////////////////////////////////////////////////////////////////
string Map::to_string_with_precision(double a_value, const int n)
{
        ostringstream out;
        out << setprecision(n) << a_value;
        return out.str();
}
