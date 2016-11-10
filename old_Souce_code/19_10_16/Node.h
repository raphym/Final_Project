#ifndef Node_H
#define Node_H
#include <string>

class Node
{
    public:
        Node(std::string n,double x, double y , int i);
        virtual ~Node();
        std::string getName();
        int getId();
        void freeMemory();
        double getLocationX();
        double getLocationY();
        bool isCoverage();
        void setCoverage(bool b);

    protected:
      std::string *name;
      int id;
      double locationX;
      double locationY;
      bool   coverage;

    private:

};

#endif // Node_H
