#include <iostream>
#include "Simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
        if(argc == 3)
        {
                string city="";
                int choice =-1;
                try
                {
                        city = argv[1];
                        choice = stoi(argv[2]);
                        if(choice!=0 && choice!=1)
                        {
                                cout << "The choice should to be 0 for test or 1 for Events-Schedule"<< endl;
                                //bip sound
                                system("canberra-gtk-play -f input_files/sounds/beep-02.wav");
                                return -1;
                        }

                }catch(exception e)
                {
                        cout << "Error of input please write : <city name><choice>"<<endl;
                        cout << "The choice should to be 0 for test or 1 for Events-Schedule"<<endl;
                        //bip sound
                        system("canberra-gtk-play -f input_files/sounds/beep-02.wav");
                        return -1;
                }

                Simulation *s= new Simulation(city);
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
                cout << "Error of input please write : <city name><choice>"<<endl;
                cout << "The choice should to be 0 for test or 1 for Events-Schedule"<<endl;
                //bip sound
                system("canberra-gtk-play -f input_files/sounds/beep-02.wav");
                return -1;
        }
}
