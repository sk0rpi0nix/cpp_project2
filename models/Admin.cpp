#include <string>
#include <iostream>
#include <headers/Admin.h>

namespace human {


void Admin::setInfo(int id, std::string name) {
    this->id = id;
    this->name = name;
}

void Admin::printInfo() {
    std::cout << "Admin ID: " << id << ", Name: " << name << std::endl;
}

}