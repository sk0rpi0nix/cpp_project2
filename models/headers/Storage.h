#ifndef STORAGE_H
#define STORAGE_H
#include <vector>
#include <map>
#include <string>
#include "headers/User.h"
#include "headers/Admin.h"
#include "headers/Message.h"
#include "headers/Vector.h"

namespace XXX {
extern Vector<User> users;
extern std::vector<Admin> admins;
extern std::vector<Message> sessionMessages;
extern std::map<std::string, std::string> usersCreds;

// Глобальные переменные состояния
extern std::string currentUserName;
extern std::string currentInterlocutorName; // Имя текущего собеседника
extern int currentMsgId;

void loadGlobalMsgId();
void saveGlobalMsgId();
}
#endif