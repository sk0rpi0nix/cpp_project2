#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include "headers/User.h"
#include "headers/Admin.h"
#include "headers/Message.h"

namespace human {
    std::vector<User> users;
    std::vector<Admin> admins;
    std::vector<Message> sessionMessages;

}

#endif