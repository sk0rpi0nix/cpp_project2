#include "AdminMenu.h"
#include "headers/Storage.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

namespace XXX {

AdminMenu::AdminMenu() {
    this->title = "Панель Администратора";
    commands["addUser"] = Cmd("addUser", cmd_addUser, "addUser <name> - добавить пользователя");
    commands["sortUsersByName"] = Cmd("sortUsersByName", cmd_sortUsersByName, "sortUsersByName - вывести пользователей по имени");
    commands["printMessages"] = Cmd("printMessages", cmd_printMessages, "printMessages - вывести все сообщения");
    commands["addMessage"] = Cmd("addMessage", cmd_addMessage, "addMessage <sender> <receiver> <text> - создать сообщение");
    commands["printUsers"] = Cmd("printUsers", cmd_printUsers, "Вывести пользователей");
    commands["logout"] = Cmd("logout", cmd_logout, "logout - выйти из аккаунта");
}

void AdminMenu::print() {
    // clearScreen();
    std::cout << "=== ПАНЕЛЬ АДМИНИСТРАТОРА ===" << std::endl;
    std::cout << "Текущий пользователь: " << currentUserName << std::endl;
    std::cout << "Всего пользователей в системе: " << users.getSize() << std::endl;
    std::cout << "===========" << std::endl;
    std::cout << "Команды:" << std::endl;
    for (std::map<std::string, Cmd>::iterator it = commands.begin(); it != commands.end(); ++it) {
        std::cout << "  " << it->second.getDesc() << std::endl;
    }
}

int AdminMenu::cmd_addUser(const std::string& args) {
    try {
        if (args.empty()) {
            throw std::invalid_argument("Имя пользователя не указано.");
        }
        
        int maxId = 0;
        for (size_t i = 0; i < users.getSize(); ++i) {
            if (users.at(i).getId() > maxId) { // Используем безопасный at()
                maxId = users.at(i).getId();
            }
        }
        
        int newId = maxId + 1;
        User newUser;
        
        // Вот здесь может сработать throw из User::setInfo, если имя пустое
        newUser.setInfo(newId, args); 
        
        users.push_back(newUser);
        usersCreds[args] = args; 
        
        std::cout << "[Success] Пользователь '" << args << "' добавлен с ID: " << newId << std::endl;
    } 
    catch (const std::invalid_argument& e) {
        std::cout << "[Ошибка добавления] " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e) {
        std::cout << "[Ошибка доступа] " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "[Непредвиденная ошибка] " << e.what() << std::endl;
    }
    
    return 0;
}

int AdminMenu::cmd_sortUsersByName(const std::string&) {
    if (users.getSize() == 0) {
        std::cout << "Список пользователей пуст." << std::endl;
        return 0;
    }
    
    // Сортируем с использованием нашего функтора и итераторов Vector
    std::sort(users.begin(), users.end(), CompareUserByName());
    
    std::cout << "--- Отсортированный список пользователей ---" << std::endl;
    for (size_t i = 0; i < users.getSize(); ++i) {
        std::cout << "  [" << users[i].getId() << "] " << users[i].getName() << std::endl;
    }
    return 0;
}

int AdminMenu::cmd_printMessages(const std::string&) {
    std::vector<Message> allMessages;
    
    // Читаем файлы всех пользователей из usersCreds
    for (std::map<std::string, std::string>::iterator it = usersCreds.begin(); it != usersCreds.end(); ++it) {
        std::string filename = "user_data/" + it->first + ".txt";
        std::ifstream file(filename.c_str());
        
        if (file.is_open()) {
            std::string line;
            while (std::getline(file, line)) {
                if (line.empty()) continue;
                std::stringstream ss(line);
                std::string id_str, receiver, text;
                
                if (std::getline(ss, id_str, ';') && 
                    std::getline(ss, receiver, ';') && 
                    std::getline(ss, text)) {
                    
                    int msgId = std::atoi(id_str.c_str());
                    // Отправитель - это владелец файла
                    allMessages.push_back(Message(msgId, it->first, receiver, text));
                }
            }
            file.close();
        }
    }
    
    if (allMessages.empty()) {
        std::cout << "Сообщения не найдены." << std::endl;
        return 0;
    }
    
    // Сортируем все сообщения по ID (используем CompareMsgById из Message.h)
    std::sort(allMessages.begin(), allMessages.end(), CompareMsgById());
    
    std::cout << "--- ВСЕ СООБЩЕНИЯ В СИСТЕМЕ ---" << std::endl;
    for (size_t i = 0; i < allMessages.size(); ++i) {
        std::cout << allMessages[i] << std::endl; // Использует operator<< из Message.cpp
    }
    return 0;
}

int AdminMenu::cmd_addMessage(const std::string& args) {
    // Ожидаемый формат: sender receiver text (текст может содержать пробелы)
    size_t pos1 = args.find(' ');
    if (pos1 == std::string::npos) {
        std::cout << "Ошибка формата. Пример: addMessage Ivan Petr Privet kak dela" << std::endl;
        return 0;
    }
    std::string sender = args.substr(0, pos1);
    
    size_t pos2 = args.find(' ', pos1 + 1);
    if (pos2 == std::string::npos) {
        std::cout << "Ошибка формата. Не указан получатель или текст." << std::endl;
        return 0;
    }
    std::string receiver = args.substr(pos1 + 1, pos2 - pos1 - 1);
    std::string text = args.substr(pos2 + 1);
    
    // Генерируем ID и создаем сообщение
    currentMsgId++;
    Message newMsg(currentMsgId, sender, receiver, text);
    
    // Сохраняем в файл отправителя
    std::string filename = "user_data/" + sender + ".txt";
    std::ofstream file(filename.c_str(), std::ios::app);
    if (file.is_open()) {
        file << newMsg.id << ";" << newMsg.receiverName << ";" << newMsg.text << std::endl;
        file.close();
        std::cout << "[Success] Сообщение от '" << sender << "' для '" << receiver << "' создано (ID: " << newMsg.id << ")." << std::endl;
    } else {
        std::cout << "[Error] Не удалось открыть файл " << filename << " для записи." << std::endl;
    }
    
    return 0;
}

int AdminMenu::cmd_printUsers(const std::string& args) {
    std::cout << "\n=== СПИСОК ВСЕХ ПОЛЬЗОВАТЕЛЕЙ ===" << std::endl;
    
    if (users.getSize() == 0) {
        std::cout << "В системе пока нет зарегистрированных пользователей." << std::endl;
    } else {
        // Используем range-based for loop. 
        // Это работает, потому что в вашем Vector.h есть begin() и end(),
        // а в User.cpp перегружен operator<< для std::ostream.
        for (const auto& user : users) {
            std::cout << "  " << user << std::endl; 
        }
    }
    
    std::cout << "=================================" << std::endl;
    return 0; // Возвращаем 0, чтобы остаться в меню админа
}

int AdminMenu::cmd_logout(const std::string&) {
    std::cout << "Выход из панели администратора..." << std::endl;
    currentUserName = "";
    return -1;
}

bool AdminMenu::start() {
    while (true) {
        int result = inputCommand();
        if (result == -1) {
            return false; // Возврат в LoginMenu
        }
    }
}

} // namespace XXX