#ifndef ADMINMENU_H
#define ADMINMENU_H
#include <string>
#include "CMenu.h"
#include "../models/headers/Cmd.h"
#include "../models/headers/User.h"

namespace XXX {
// Функтор для сортировки пользователей по имени (C++98 стиль)
struct CompareUserByName {
    bool operator()(const User& a, const User& b) const {
        // Предполагается, что в Human/User есть метод getName()
        return a.getName() < b.getName(); 
    }
};

class AdminMenu : public CMenu {
public:
    AdminMenu();
    void print() override;
    bool start() override;

private:
    static int cmd_addUser(const std::string& args);
    static int cmd_printUsers(const std::string& args);
    static int cmd_sortUsersByName(const std::string& args);
    static int cmd_printMessages(const std::string& args);
    static int cmd_addMessage(const std::string& args);
    static int cmd_logout(const std::string& args);
};
}
#endif