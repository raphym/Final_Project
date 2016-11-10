#ifndef LAMP_H
#define LAMP_H

#include <string>


class Lamp
{
    public:
        Lamp(std::string n ,double x, double y);
        virtual ~Lamp();
        std::string getName();
        void freeMemory();
        double getLocationX();
        double getLocationY();
        bool isCoverage();
        void setCoverage(bool b);

    protected:

    private:
        std::string *name;
        double locationX;
        double locationY;
        bool   coverage;
};

#endif // LAMP_H
