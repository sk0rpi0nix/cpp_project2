#ifndef DIALOGMENU_H
#define DIALOGMENU_H
#include <string>
#include "CMenu.h"
#include "headers/User.h"

namespace XXX {
class DialogMenu : public CMenu {
public:
    DialogMenu(User* interlocutor);
    void print() override;
    bool start() override;

private:
    User* targetUser;
    
    // Статические обработчики команд
    static int cmd_logout(const std::string& args);
    static int cmd_write(const std::string& args);
    
    // Вспомогательная функция загрузки диалога
    static void loadDialogMessages(const std::string& user1, const std::string& user2);
};
}
#endif