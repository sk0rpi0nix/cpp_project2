#include "UserMenu.h"
#include "DialogMenu.h"
#include "headers/Storage.h"
#include <iostream>

namespace XXX {

UserMenu::UserMenu() {
    this->title = "Главное меню";
    commands["logout"] = Cmd("logout", cmd_logout, "logout - выйти из аккаунта");
    commands["select"] = Cmd("select", cmd_select, "select <имя> - выбрать собеседника");
}

void UserMenu::print() {
    clearScreen(); // Если вы добавили этот метод в CMenu
    std::cout << "=== СПИСОК ПОЛЬЗОВАТЕЛЕЙ ===" << std::endl;
    std::cout << "Текущий пользователь: " << currentUserName << std::endl;
    std::cout << "Доступные собеседники:" << std::endl;
    
    // Проходим по всем пользователям
    for (size_t i = 0; i < users.getSize(); ++i) { // Замените на users.size(), если нужно
        User u = users[i]; 
        // Исключаем текущего пользователя из списка
        if (u.getName() != currentUserName) { // Замените getName() на актуальный геттер из Human
            std::cout << "  - " << u.getName() << std::endl;
        }
    }
    
    std::cout << "===========" << std::endl;
    std::cout << "Команды:" << std::endl;
    for (std::map<std::string, Cmd>::iterator it = commands.begin(); it != commands.end(); ++it) {
        std::cout << "  " << it->second.getDesc() << std::endl;
    }
}

User* UserMenu::findUserByName(const std::string& name) {
    for (size_t i = 0; i < users.getSize(); ++i) {
        if (users[i].getName() == name) {
            return &users[i]; // Возвращаем указатель на элемент в векторе
        }
    }
    return nullptr;
}

int UserMenu::cmd_logout(const std::string& args) {
    std::cout << "Выход из аккаунта..." << std::endl;
    currentUserName = ""; // Очищаем текущего пользователя
    return -1; // Возврат -1 прерывает цикл UserMenu и возвращает в LoginMenu
}

int UserMenu::cmd_select(const std::string& args) {
    if (args.empty()) {
        std::cout << "Укажите имя пользователя после команды select." << std::endl;
        return 0;
    }
    
    User* target = findUserByName(args);
    if (!target) {
        std::cout << "Пользователь '" << args << "' не найден." << std::endl;
        return 0;
    }
    
    if (target->getName() == currentUserName) {
        std::cout << "Нельзя выбрать самого себя." << std::endl;
        return 0;
    }
    
    std::cout << "Переход к диалогу с " << args << "..." << std::endl;
    
    // Создаем DialogMenu и передаем управление ему
    DialogMenu dialogMenu(target);
    dialogMenu.start();
    
    // Когда dialogMenu.start() завершится, мы вернемся сюда, 
    // и цикл UserMenu продолжит работу (снова покажется print)
    return 0;
}

bool UserMenu::start() {
    while (true) {
        int result = inputCommand();
        if (result == -1) {
            return false; // Выход из UserMenu
        }
    }
}

} // namespace XXX