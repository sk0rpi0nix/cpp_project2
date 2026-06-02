#include "headers/Storage.h"
#include <fstream>
#include <iostream>

namespace XXX {
Vector<User> users;
std::vector<Admin> admins;
std::vector<Message> sessionMessages;
std::map<std::string, std::string> usersCreds;

std::string currentUserName = "";
std::string currentInterlocutorName = "";
int currentMsgId = 0;

void loadGlobalMsgId() {
    std::ifstream file("user_data/curMsgID.bin", std::ios::binary);
    if (file.is_open()) {
        file.read(reinterpret_cast<char*>(&currentMsgId), sizeof(currentMsgId));
        file.close();
    }
}

void saveGlobalMsgId() {
    std::ofstream file("user_data/curMsgID.bin", std::ios::binary);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&currentMsgId), sizeof(currentMsgId));
        file.close();
    }
}
}