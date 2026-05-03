// models/Storage.cpp
#include "headers/Storage.h" // Подключаем заголовок, где есть extern

namespace XXX {

    
    UserVector users;
    std::vector<Admin> admins;
    std::vector<Message> sessionMessages;
    std::map<std::string, std::string> usersCreds;

}