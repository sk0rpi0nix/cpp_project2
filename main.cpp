
#include <iostream>
#include <string>
#include "menu/CMenu.h"
#include "menu/CMenuItem.h"
#include "models/headers/User.h"
#include "models/headers/Admin.h"
#include "models/headers/Storage.h"
#include "models/headers/Message.h"



using namespace XXX;
using namespace human;

int idBuf = 0;

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
int printUsers() {
    for (User &u : users) {
        u.printInfo();
    }
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
        m.printMessage();
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

const int ITEMS_NUMBER = 5;

int main() {
    CMenuItem items[ITEMS_NUMBER] {
        CMenuItem{"add user", createUser},
        CMenuItem{"print all users", printUsers},
        CMenuItem{"add message", addMsg},
        CMenuItem{"print messages", printMsgs},
        CMenuItem{"add admin", addAdmin},
    };
    CMenu menu("My console menu", items, ITEMS_NUMBER);
    while (menu.runCommand()) {};
    return 0;
}