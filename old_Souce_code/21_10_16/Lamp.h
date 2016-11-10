#ifndef LAMP_H
#define LAMP_H
#include <string>


class Lamp
{
    public:
        Lamp(std::string n ,double x, double y, int id);
        virtual ~Lamp();
        std::string getName();
        int getId();
        void freeMemory();
        double getLocationX();
        double getLocationY();
        bool isCoverage();
        void setCoverage(bool b);

    protected:

    private:
        std::string *name;
        //static int counterLamps;
        int id;
        double locationX;
        double locationY;
        bool   coverage;
};

#endif // LAMP_H
