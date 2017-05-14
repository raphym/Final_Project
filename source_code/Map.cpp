#include "Map.h"
using namespace std;

Map::Map(string name,string fileProviders, string fileLamps, string fileTrafficLights)   //ctor
{
        this->name=name;
        this->fileProviders=fileProviders;
        this->fileLamps=fileLamps;
        this->fileTrafficLights=fileTrafficLights;

        loadMap();
}

Map::~Map()
{
        for(int i=0; i<vecElementsOfTheMap.size(); i++)
        {
                if(vecElementsOfTheMap[i]!=NULL)
                        delete vecElementsOfTheMap[i];
        }

}


vector<Node*> Map::loadLamps()
{
        int i=0;
        //f is a FileStream Object to read informations about the lamps
        FileStream f(this->fileLamps);
        int nbLamps = f.LineCounters();
        if (nbLamps==0)
        {
                cout << "your file : " << this->fileLamps << " is corrupted"<< endl;
                exit(-1);
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
                lamps.push_back(new Node("LAMP",names[i],New_Node_Id,posX[i],posY[i]));
        delete [] posX;
        delete [] posY;
        delete [] names;

        return lamps;
}


vector<Node*> Map::loadProviders()
{
        int i=0;

        //f is a FileStream Object to read informations about the providers
        FileStream f(this->fileProviders);
        int nbProviders = f.LineCounters();
        if (nbProviders==0)
        {
                cout << "your file : " << this->fileProviders << " is corrupted"<< endl;
                exit(-1);
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
                providers.push_back(new Node("PROVIDER",names[i],New_Node_Id,posX[i],posY[i]));
        delete [] posX;
        delete [] posY;
        delete [] names;

        return providers;
}

vector<Node*> Map::loadTrafficLights()
{
        int i=0;
        //f is a FileStream Object to read informations about the trafficLights
        FileStream f(this->fileTrafficLights);
        int nbTrafficLight = f.LineCounters();
        if (nbTrafficLight==0)
        {
                cout << "your file : " << this->fileTrafficLights << " is corrupted"<< endl;
                exit(-1);
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
                trafficLights.push_back(new Node("TRAFFIC_LIGHT",names[i],New_Node_Id,posX[i],posY[i]));
        delete [] posX;
        delete [] posY;
        delete [] names;

        return trafficLights;
}

void Map::loadMap()
{
        //regroupper tous les elements:
        vector<Node*> lamps= loadLamps();
        vector<Node*>providers=loadProviders();
        vector<Node*>trafficLights=loadTrafficLights();
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

}
//add a node
void Map::addNode(Node *n)
{
        if(n==NULL)
                return;
        vecElementsOfTheMap.push_back(n);
}


//remove a node
void Map::removeNode(int id)
{
        for(int i=0; i < vecElementsOfTheMap.size(); i++)
        {
                if(vecElementsOfTheMap[i]->getId() == id)
                        vecElementsOfTheMap[i]->erase();
        }

}
// return a vectors of all elements of the map (nodes)
vector<Node*> Map::getNodes()
{
        return vecElementsOfTheMap;
}

// print the map
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

//Refresh the scan hotspots of each node in the map
void Map::refreshMap()
{
        Node *currentNode = NULL;
        for(int i=0; i<vecElementsOfTheMap.size(); i++)
        {
                currentNode   = vecElementsOfTheMap[i];
                currentNode->scanHotspots(vecElementsOfTheMap,currentNode->getVectAvailableNodes());
        }
}

//clear the map of deleted elements
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


//Function which running BFS on a single Node
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


//reset visited
void Map::resetVisited()
{
        for(int i=0; i < vecElementsOfTheMap.size(); i++)
                vecElementsOfTheMap[i]->setVisited(RESET);
}

//Function which construct the quorums it's running the function runBFS
void Map::quorumConstruct()
{
        // For BFS
        resetVisited();
        int currentId = 0;//35
        //int currentId = 47;
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

                        Backbone *b = new Backbone("Backbone",name,oldId,posX,posY);
                        b->setToBeBackbone();
                        for(int k=0; k< sizeOfQuorum; k++)
                                b->addTolistOfQuorum(current->getlistOfQuorum()[k]);

                        vecElementsOfTheMap[i]=b;
                        delete current;
                }
        }
        refreshMap();
}

//print the quorums
void Map::printListOfQuorum()
{
        for(int i=0; i<vecElementsOfTheMap.size(); i++)
        {
                cout << endl;
                cout << "Name : " << vecElementsOfTheMap[i]->getName();
                cout << " Voisins : ";
                int size = vecElementsOfTheMap[i]->getlistOfQuorum().size();
                if(vecElementsOfTheMap[i]->isItBackbone()==true)
                        for(int j=0; j< size; j++)
                        {
                                int id = vecElementsOfTheMap[i]->getlistOfQuorum()[j];
                                cout << " " <<  vecElementsOfTheMap[id]->getName();
                        }
                cout << endl;
        }
}

//check if a specific Node exists in a vector
bool Map::check(vector<Node *> bfsNodes, int id)
{
        for (int i = 0; i < bfsNodes.size(); i++)
        {
                if (bfsNodes[i]->getId() == id)
                        return true;
        }
        return false;
}
//check if a specific Node exists in a vector
bool Map::check(vector<int> bfsNodes, int id)
{
        for (int i = 0; i < bfsNodes.size(); i++)
        {
                if (bfsNodes[i] == id)
                        return true;
        }
        return false;
}

//Construct the traceroutes for the nodes of the graph
void Map::constructAllTraceroute()
{
        int numsOfNodes = vecElementsOfTheMap.size();
        for(int i=0; i < numsOfNodes; i++)
        {
                constructTraceroute(vecElementsOfTheMap[i]->getId());
        }
}

//Construct a traceroute for a specific node
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

//run DFS recursive to construct a traceroute
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

                for (int i = 1; i<path_index; i++)
                {
                        traceroute->push_back(path[i]);
                }
                //add the vect of traceroute to the traceroute of the origin node
                vecElementsOfTheMap[idOrigin]->getTheTraceroute().push_back(*traceroute);
                delete traceroute;
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

void Map::printTraceroute()
{

        cout << endl << "Print of TraceRoute for each node" << endl << endl;

        for(int i=0; i<vecElementsOfTheMap.size(); i++)
        {
                vecElementsOfTheMap[i]->printTraceroute();
        }

        cout << "END of print TraceRoute" << endl<< endl;

}
