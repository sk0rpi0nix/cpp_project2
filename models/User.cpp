#include <string>
#include <iostream>
#include "headers/User.h"
#include "headers/Human.h"
#include <stdexcept>

namespace XXX {
    void User::setInfo(int id, std::string name) {
        // 1. Проверка на логическую недопустимость значений
        if (id < 0) {
            throw std::invalid_argument("ID пользователя не может быть отрицательным.");
        }
        if (name.empty()) {
            throw std::invalid_argument("Имя пользователя не может быть пустым.");
        }
        
        this->id = id;
        this->name = name;
    }

    void User::printInfo() {
        std::cout << "User ID: " << id << ", Name: " << name << std::endl;
    }
    // std::string User::getName() {
    //     return this->name;
    // }
    std::string Human::getName() const { 
        return name; 
    }

    int Human::getId() const { 
        return id; 
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