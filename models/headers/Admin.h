#ifndef ADMIN_H
#define ADMIN_H

#include <string>
#include <iostream>
#include "headers/Human.h"

namespace human {
    class Admin : public Human {
    public:
        void setInfo(int id, std::string name);

        void printInfo();
    };
}



#endif