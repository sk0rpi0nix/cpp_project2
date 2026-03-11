#include <string>
#include <iostream>
#include <headers/User.h>

namespace human {
    void User::setInfo(int id, std::string name) {
        this->id = id;
        this->name = name;
    }

    void User::printInfo() {
        std::cout << "User ID: " << id << ", Name: " << name << std::endl;
    }

}