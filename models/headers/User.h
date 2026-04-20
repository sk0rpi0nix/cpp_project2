#ifndef USER_H
#define USER_H

#include <string>
#include <iostream>
#include "Human.h"

namespace XXX {
    class User : public Human {
    public:
        void setInfo(int id, std::string name);

        void printInfo();

    friend std::ofstream& operator<<(std::ofstream& ofs, const User& user);
    friend std::ostream& operator<<(std::ostream& os, const User& user); // Для cout

    // 2. Перегрузки операторов сравнения как методов внутри класса
    // Сравнение по ID (основной ключ)
    bool operator==(const User& other) const;
    bool operator!=(const User& other) const;
    
    // Операторы для сортировки (например, по имени или ID)
    // Пусть сортировка будет по имени, а при равенстве имен - по ID
    bool operator<(const User& other) const;
    bool operator>(const User& other) const;
    bool operator<=(const User& other) const;
    bool operator>=(const User& other) const;
    };
}



#endif