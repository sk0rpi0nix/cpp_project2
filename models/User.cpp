#include <string>
#include <iostream>
#include "headers/User.h"
#include "headers/Human.h"

namespace XXX {
    void User::setInfo(int id, std::string name) {
        this->id = id;
        this->name = name;
    }

    void User::printInfo() {
        std::cout << "User ID: " << id << ", Name: " << name << std::endl;
    }

    
    // Дружественная функция вывода в консоль (для удобства)
    std::ostream& operator<<(std::ostream& os, const User& user) {
        os << "User[ID: " << user.id << ", Name: " << user.name << "]";
        return os;
    }
    
    // 2. Перегрузки операторов сравнения (методы класса)

    bool User::operator==(const User& other) const {
        return this->name == other.name;
    }

    bool User::operator!=(const User& other) const {
        return !(this->name == other.name);
    }

    // Логика сортировки: сначала по имени (алфавит), потом по ID
    bool User::operator<(const User& other) const {
        if (this->name != other.name) {
            return this->name < other.name;
        }
        return this->id < other.id;
    }

    bool User::operator>(const User& other) const {
        return other.name < this->name;
    }

    bool User::operator<=(const User& other) const {
        return !(other.name < this->name);
    }

    bool User::operator>=(const User& other) const {
        return !(this->name < other.name);
    }

}