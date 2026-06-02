#ifndef USERMENU_H
#define USERMENU_H
#include <string>
#include "CMenu.h"
#include "../models/headers/Cmd.h"
#include "headers/User.h"

namespace XXX {
class UserMenu : public CMenu {
public:
    void print() override;
    bool start() override;
    UserMenu();

private:
    static int cmd_logout(const std::string& args);
    static int cmd_select(const std::string& args);
    
    // Функция поиска пользователя по имени
    static User* findUserByName(const std::string& name);
};
}
#endif