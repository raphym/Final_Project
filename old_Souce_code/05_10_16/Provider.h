#ifndef PROVIDER_H
#define PROVIDER_H

#include <string>


class Provider
{
    public:
        Provider(std::string n ,double x, double y);
        virtual ~Provider();
        std::string getName();
        void freeMemory();
        double getLocationX();
        double getLocationY();


    protected:

    private:
        std::string *name;
        double locationX;
        double locationY;
        //bool   coverage;
};

#endif // PROVIDER_H
