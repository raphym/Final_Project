#include <iostream>
#include "Simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
        if(argc == 4)
        {
                string city="";
                int choice =-1;
                int max_hop=-1;
                try
                {
                        city = argv[1];
                        choice = stoi(argv[2]);
                        max_hop = stoi(argv[3]);
                        if(choice!=0 && choice!=1)
                        {
                                cout << "The choice should to be 0 for test or 1 for Events-Schedule"<< endl;
                                //bip sound
                                system("canberra-gtk-play -f input_files/sounds/beep-02.wav");
                                return -1;
                        }

                }catch(exception e)
                {
                        cout << "Error of input please write : <city name><choice><max_hop>"<<endl;
                        cout << "The choice should to be 0 for test or 1 for Events-Schedule"<<endl;
                        //bip sound
                        system("canberra-gtk-play -f input_files/sounds/beep-02.wav");
                        return -1;
                }

                Simulation *s= new Simulation(city,max_hop);
                if(s->getLoaded())
                {
                        s->startSim(choice);
                        delete s;
                        //bip sound
                        system("canberra-gtk-play -f input_files/sounds/beep-02.wav");
                        return 0;
                }
                else
                {
                        delete s;
                        //bip sound
                        system("canberra-gtk-play -f input_files/sounds/beep-02.wav");
                        return -1;
                }
        }
        else
        {
                cout << "Error of input please write : <city name><choice><max_hop>"<<endl;
                cout << "The choice should to be 0 for test or 1 for Events-Schedule"<<endl;
                //bip sound
                system("canberra-gtk-play -f input_files/sounds/beep-02.wav");
                return -1;
        }
}
