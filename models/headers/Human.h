#ifndef HUMAN_H
#define HUMAN_H

#include <string>

namespace XXX {


    class Human { //
    protected:
        int id;
        std::string name;

    public:
        virtual void setInfo(int id, std::string name) = 0;
        virtual void printInfo() = 0;
     
    };
}

#endif