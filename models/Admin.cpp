#include <string>
#include <iostream>
#include <headers/Admin.h>
#include "headers/Human.h"

namespace XXX {


void Admin::setInfo(int id, std::string name) {
    this->id = id;
    this->name = name;
}

void Admin::printInfo() {
    std::cout << "Admin ID: " << id << ", Name: " << name << std::endl;
}

std::ostream& operator<<(std::ostream& os, Admin admin) {
    std::cout << "Admin id: " << admin.id << "Admin name" << admin.name;
    return os;
}

}