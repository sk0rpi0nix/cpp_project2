#include "DialogMenu.h"
#include "headers/Storage.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

namespace XXX {

DialogMenu::DialogMenu(User* interlocutor) : targetUser(interlocutor) {
    this->title = "Диалог";
    commands["logout"] = Cmd("logout", cmd_logout, "logout - вернуться к списку пользователей");
    commands["write"] = Cmd("write", cmd_write, "write <текст> - отправить сообщение");
}

void DialogMenu::loadDialogMessages(const std::string& user1, const std::string& user2) {
    sessionMessages.clear();
    std::string files[2] = { "user_data/" + user1 + ".txt", "user_data/" + user2 + ".txt" };
    
    for (int i = 0; i < 2; ++i) {
        std::ifstream file(files[i].c_str());
        if (!file.is_open()) continue;
        
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            std::stringstream ss(line);
            std::string id_str, receiver, text;
            
            if (std::getline(ss, id_str, ';') && 
                std::getline(ss, receiver, ';') && 
                std::getline(ss, text)) {
                
                if (receiver == user1 || receiver == user2) {
                    int msgId = std::atoi(id_str.c_str());
                    std::string sender = (i == 0) ? user1 : user2;
                    sessionMessages.push_back(Message(msgId, sender, receiver, text));
                }
            }
        }
        file.close();
    }
    
    std::sort(sessionMessages.begin(), sessionMessages.end(), CompareMsgById());
}

void DialogMenu::print() {
    clearScreen();
    std::cout << "=== ДИАЛОГ С " << currentInterlocutorName << " ===" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    size_t total = sessionMessages.size();
    size_t start_idx = (total > 10) ? total - 10 : 0;
    
    if (total == 0) {
        std::cout << "(История сообщений пуста)" << std::endl;
    } else {
        for (size_t i = start_idx; i < total; ++i) {
            std::cout << sessionMessages[i] << std::endl;
        }
    }
    
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Команды:" << std::endl;
    for (std::map<std::string, Cmd>::iterator it = commands.begin(); it != commands.end(); ++it) {
        std::cout << "  " << it->second.getDesc() << std::endl;
    }
}

int DialogMenu::cmd_logout(const std::string& args) {
    std::cout << "Возврат к списку пользователей..." << std::endl;
    return -1;
}

int DialogMenu::cmd_write(const std::string& args) {
    if (args.empty()) {
        std::cout << "Ошибка: введите текст сообщения после команды write." << std::endl;
        return 0;
    }
    
    // Используем глобальные переменные вместо нестатического targetUser
    currentMsgId++;
    
    Message newMsg(currentMsgId, currentUserName, currentInterlocutorName, args);
    sessionMessages.push_back(newMsg);
    
    std::string filename = "user_data/" + currentUserName + ".txt";
    std::ofstream file(filename.c_str(), std::ios::app);
    if (file.is_open()) {
        file << newMsg.id << ";" << newMsg.receiverName << ";" << newMsg.text << std::endl;
        file.close();
        std::cout << "Сообщение отправлено." << std::endl;
    } else {
        std::cout << "Ошибка: не удалось открыть файл для записи." << std::endl;
    }
    
    return 0;
}

bool DialogMenu::start() {
    // КЛЮЧЕВОЙ МОМЕНТ: Сохраняем имя собеседника в глобальную переменную 
    // ДО запуска цикла, чтобы статический cmd_write мог его использовать
    currentInterlocutorName = targetUser->getName(); 
    
    loadDialogMessages(currentUserName, currentInterlocutorName);
    
    while (true) {
        int result = inputCommand();
        if (result == -1) {
            return false;
        }
    }
}

} // namespace XXX