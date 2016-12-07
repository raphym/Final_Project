#ifndef PROVIDER_H
#define PROVIDER_H

#include <string>


class Provider
{
    public:
        Provider(std::string n ,double x, double y, int i);
        virtual ~Provider();
        std::string getName();
        int getId();
        void freeMemory();
        double getLocationX();
        double getLocationY();


    protected:

    private:
        std::string *name;
        int id;
        double locationX;
        double locationY;
        //bool   coverage;
};

#endif // PROVIDER_H
