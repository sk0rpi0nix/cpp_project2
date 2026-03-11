#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include "Human.h"

namespace human {
    class User : public Human {
    public:
        void setInfo(int id, std::string name);

        void printInfo();
    };
}



#endif