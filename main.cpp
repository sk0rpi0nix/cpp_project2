#include <algorithm>
#include <iostream>
#include <string>
#include "menu/CMenu.h"
#include "menu/CMenuItem.h"
#include "models/headers/User.h"
#include "models/headers/Admin.h"
#include "models/headers/Storage.h"
#include "models/headers/Message.h"
// #include "models/headers/LoginMenu.h"
#include "menu/LoginMenu.h"


// int idBuf = 0;

// namespace XXX {
//     int createUser() {
//         string name;

//         cout << "Enter name: ";
//         cin >> name;

//         User u;
//         u.setInfo(idBuf, name);
//         idBuf++;
//         users.push_back(u);

//         cout << endl;
//         return 1;
//     }

//     int sortUserByName() {
//         std::sort(users.begin(), users.end(), [](const User& a, const User& b) {
//             return a < b;
//         });
//         return 1;
//     }

//     int printUsers() {
//         for (User &u : users) {
//             cout << u << "\n";
//         };
//         return 1;
//     }
//     int addMsg() {
//         int id, userId;
//         string text;

//         cout << "Message id: ";
//         cin >> id;

//         cout << "User id: ";
//         cin >> userId;

//         cout << "Text: ";
//         cin >> text;

//         Message msg = Message{id, userId,text};

//         sessionMessages.push_back(msg);

//         return 1;
//     }
//     int printMsgs() {
//         for (Message &m : sessionMessages) {
//             cout << m;
//         }
//         return 1;
//     }
//     // int addAdmin() {
//     //     int id;
//     //     string name;

//     //     cout << "Enter id: ";
//     //     cin >> id;

//     //     cout << "Enter name: ";
//     //     cin >> name;

//     //     User u;
//     //     u.setInfo(id, name);

//     //     users.push_back(u);

//     //     return 1;
//     // }

//     const int ITEMS_NUMBER = 6;
    
//     int clearScreen() {
//         // \033[2J clears the screen, \033[H moves the cursor to the top-left corner
//         std::cout << "\033[2J\033[H" << std::flush;
//         return 1;
//     }

// }



// using namespace XXX;

int main() {
    // 1. Загружаем глобальный ID сообщений при старте
    XXX::loadGlobalMsgId();
    
    // 2. Запускаем меню авторизации
    XXX::LoginMenu loginMenu;
    loginMenu.start();
    
    // 3. Сохраняем глобальный ID перед закрытием программы
    XXX::saveGlobalMsgId();
    
    cout << "Программа завершена." << endl;
    return 0;
}