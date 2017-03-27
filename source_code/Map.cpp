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
                                vecElementsOfTheMap[neighborsId]->addTolistOfQuorum(currentNode->getId());
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
        int currentId = 35;
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
//run on DFS on each node of the Map
void Map::DFS()
{
        std::vector<Node*> graph;
        for(int i=0; i< vecElementsOfTheMap.size(); i++)
        {
                graph.push_back(vecElementsOfTheMap[i]);
        }

        for(int i=0; i< graph.size(); i++)
        {
                //print test
                //cout << endl << "RUN DFS on " << graph[i]->getName() << endl;
                resetVisited();
                //for each node of the graph create a vector for a traceroute
                std::vector<string> vectName;
                std::vector<int> vectID;
                std::vector <int>vectTracerouteIsItBackbone;



                DFS_Visit(graph,graph[i],vectName,vectID,vectTracerouteIsItBackbone);
                //when finish push the node into the vector Traceroute of the node

                std::vector<int>*theTrace = new std::vector<int>();
                refreshMap();
                vector <Node*> vecNodeAvailableFromCurrent;
                vecNodeAvailableFromCurrent.clear();
                graph[i]->scanHotspots(graph[i]->getVectAvailableNodes(), vecNodeAvailableFromCurrent);



                for(int j=0; j<vectID.size(); j++ )
                {

                        if(vectTracerouteIsItBackbone[j]==0)
                        {
                                theTrace->push_back(vectID[j]);
                        }
                        else
                        {
                                theTrace->push_back(vectID[j]);
                                graph[i]->getTheTraceroute().push_back(*theTrace);
                                delete theTrace;
                                theTrace = new std::vector<int>();
                                //it is a new vector so go search the available node from the graph[i]
                                j++;
                                bool b = false;
                                while(b== false && j<vectID.size())
                                {
                                        for(int l=0; l<vecNodeAvailableFromCurrent.size(); l++)
                                        {
                                                if(vectID[j] == vecNodeAvailableFromCurrent[l]->getId() )
                                                {
                                                        j=j-2;
                                                        b=true;
                                                        break;
                                                }
                                        }
                                        j++;
                                }
                        }
                }

                if(theTrace!=NULL)
                        delete theTrace;
        }
}


void Map::DFS_Visit(std::vector<Node *> graph, Node *current,std::vector<string>& vectName,std::vector<int>& vectID,std::vector<int>&vectTracerouteIsItBackbone)
{
        current->setVisited(INCREMENT); //to 1 (GREY)
        //Discover the neighbors of the currentNode
        std::vector<Node*> neighbors;
        current->scanHotspots(graph,neighbors);
        for(int i=0; i< neighbors.size(); i++)
        {
                if(neighbors[i]->getVisited()==0)
                {
                        //print test
                        //cout << "from : " << current->getName() << " to : " << neighbors[i]->getName() << endl;
                        vectName.push_back(neighbors[i]->getName());
                        vectID.push_back(neighbors[i]->getId());
                        if(neighbors[i]->isItBackbone())
                        {
                                vectTracerouteIsItBackbone.push_back(1);
                                continue;
                        }

                        else
                        {
                                vectTracerouteIsItBackbone.push_back(0);
                                DFS_Visit(graph,neighbors[i],vectName,vectID,vectTracerouteIsItBackbone);
                        }
                }
        }
        current->setVisited(INCREMENT); //to 2 (BLACK)
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
