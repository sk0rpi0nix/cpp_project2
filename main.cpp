#include <algorithm>
#include <iostream>
#include <string>
#include "menu/CMenu.h"
#include "menu/CMenuItem.h"
#include "models/headers/User.h"
#include "models/headers/Admin.h"
#include "models/headers/Storage.h"
#include "models/headers/Message.h"
#include "models/headers/LoginMenu.h"



int idBuf = 0;

namespace XXX {
    int createUser() {
        int id;
        string name;

        cout << "Enter id: ";
        cin >> id;

        cout << "Enter name: ";
        cin >> name;

        User u;
        u.setInfo(id, name);

        users.push_back(u);

        return 1;
    }

    int sortUserByName() {
        std::sort(users.begin(), users.end());
        return 1;
    }

    int printUsers() {
        for (User &u : users) {
            cout << u << "\n";
        };
        return 1;
    }
    int addMsg() {
        int id, userId;
        string text;

        cout << "Message id: ";
        cin >> id;

        cout << "User id: ";
        cin >> userId;

        cout << "Text: ";
        cin >> text;

        Message msg = Message{id, userId,text};

        sessionMessages.push_back(msg);

        return 1;
    }
    int printMsgs() {
        for (Message &m : sessionMessages) {
            cout << m;
        }
        return 1;
    }
    int addAdmin() {
        int id;
        string name;

        cout << "Enter id: ";
        cin >> id;

        cout << "Enter name: ";
        cin >> name;

        User u;
        u.setInfo(id, name);

        users.push_back(u);

        return 1;
    }

    const int ITEMS_NUMBER = 6;

}

using namespace XXX;

int main() {
    CMenuItem items[ITEMS_NUMBER] {
        CMenuItem{"print all users", printUsers},
        CMenuItem{"sort users by name", sortUserByName},
        CMenuItem{"add user", createUser},
        CMenuItem{"add message", addMsg},
        CMenuItem{"print messages", printMsgs},
        CMenuItem{"add admin", addAdmin},
    };
    CMenu mainMenu("My console menu", items, ITEMS_NUMBER);
    LoginMenu loginMenu(&mainMenu);
    while (loginMenu.start()) {};
    return 0;
}