// LoginMenu.h
#ifndef LOGINMENU_H
#define LOGINMENU_H
#include <string>
#include <map>
#include "CMenu.h"

namespace XXX {
class UserMenu; // Forward declaration

class LoginMenu : public CMenu {
public:
    void print() override;
    bool start() override;
    LoginMenu();
    LoginMenu(const std::string& title);

private:
    // Все методы команд и работы с БД статические, чтобы работать с typedef int (*cmdFunc)(string)
    static int cmd_login(const std::string& creds);
    static bool loadUsersFromFile(const std::string& filename);
    static bool validateCredentials(const std::string& login, const std::string& password);
    
    // Статическая база данных (одна на все экземпляры, что логично для БД)
    static std::map<std::string, std::string> usersDatabase;
};
}
#endif