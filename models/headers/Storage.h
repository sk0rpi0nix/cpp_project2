#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include <map>
#include "headers/User.h"
#include "headers/Admin.h"
#include "headers/Message.h"

namespace XXX {
    extern std::vector<User> users;
    extern std::vector<Admin> admins;
    extern std::vector<Message> sessionMessages;
    extern std::map<std::string, std::string> usersCreds;

}

#endif