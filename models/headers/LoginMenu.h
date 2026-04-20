#ifndef LOGINMENU_H
#define LOGINMENU_H

#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <sstream>
#include "../../menu/CMenu.h"



namespace XXX {

    class Cmenu;

    class LoginMenu {
    private:
        // База данных пользователей: Логин Пароль
        std::map<std::string, std::string> usersDatabase;
        
        CMenu* mainMenuPtr; 
    
        bool loadUsersFromFile(const std::string& filename);
        bool validateCredentials(const std::string& login, const std::string& password);
    
    public:
        LoginMenu(CMenu* mainMenu);
        
        bool start();
    };
}

#endif