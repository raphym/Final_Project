#include "Node.h"

class Node
{
    public:
        Node();
        virtual ~Node();
        std::string getName();
        int getId();
        //void freeMemory();
        double getLocationX();
        double getLocationY();
        bool isCoverage();
        void setCoverage(bool b);

    protected:

    private:
        std::string *name;
        int id;
        double locationX;
        double locationY;
        bool   coverage;
};

#endif // LAMP_H
