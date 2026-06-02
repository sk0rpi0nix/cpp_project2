// LoginMenu.cpp
#include "LoginMenu.h"
#include "UserMenu.h"
#include "../models/headers/Storage.h"
#include <filesystem>
#include "AdminMenu.h"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>

namespace XXX {

// Инициализация статической переменной (обязательно в .cpp файле)
std::map<std::string, std::string> LoginMenu::usersDatabase;

LoginMenu::LoginMenu() : LoginMenu("Авторизация") {}

LoginMenu::LoginMenu(const std::string& title) {
    this->title = title;
    loadUsersFromFile("users_db.txt");
    
    // Регистрируем команды. Третий аргумент - описание для print()
    // Используем operator[] вместо emplace для совместимости с C++98
    commands["login"] = Cmd("login", cmd_login, "login логин;пароль - вход в систему");
}

void LoginMenu::print() {
    clearScreen();
    std::cout << "=== СИСТЕМА АВТОРИЗАЦИИ ===" << std::endl;
    std::cout << "Зарегистрированные пользователи:" << std::endl;
    if (usersDatabase.empty()) {
        std::cout << "  (база пуста, создайте файл users_db.txt)" << std::endl;
    } else {
        for (std::map<std::string, std::string>::iterator it = usersDatabase.begin(); 
             it != usersDatabase.end(); ++it) {
            std::cout << "  - " << it->first << std::endl; // Пароли не светим
        }
    }
    
    // 2. Разделитель
    std::cout << "===========" << std::endl;
    
    // 3. Список команд с кратким пояснением
    std::cout << "Доступные команды:" << std::endl;
    for (std::map<std::string, Cmd>::iterator it = commands.begin(); 
         it != commands.end(); ++it) {
        std::cout << "  " << it->second.getDesc() << std::endl;
    }
    std::cout << "  exit - выход из программы" << std::endl;
}

bool LoginMenu::validateCredentials(const std::string& login, const std::string& password) {
    std::map<std::string, std::string>::iterator it = usersDatabase.find(login);
    return (it != usersDatabase.end() && it->second == password);
}

bool LoginMenu::loadUsersFromFile(const std::string& filename) {
    // std::cout << "[DEBUG] Текущая рабочая директория: " << std::filesystem::current_path() << std::endl;
    // std::cout << "[DEBUG] Пытаемся открыть: " << std::filesystem::absolute(filename) << std::endl;

    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cout << "[Warning] Файл базы пользователей не найден." << std::endl;
        return false;
    }
    std::string line;
    int nextId = 1; // Счетчик для генерации ID
    
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        std::istringstream iss(line);
        std::string login, password;
        if (iss >> login >> password) {
            usersCreds[login] = password;
            usersDatabase[login] = password;
            
            // --- СИНХРОНИЗАЦИЯ С Vector<User> ---
            User newUser;
            newUser.setInfo(nextId++, login);
            users.push_back(newUser); // Предполагаем, что в Vector есть push_back
        }
    }
    file.close();
    return true;
}

int LoginMenu::cmd_login(const std::string& creds) {
    try {
        size_t spacePos = creds.find(';');
        
        // Явная валидация формата перед вызовом substr
        if (spacePos == string::npos) {
            throw std::invalid_argument("Неверный формат. Используйте: логин;пароль");
        }
        
        string login = creds.substr(0, spacePos);
        string pass = creds.substr(spacePos + 1);
        
        if (login.empty() || pass.empty()) {
            throw std::invalid_argument("Логин и пароль не могут быть пустыми.");
        }

        if (validateCredentials(login, pass)) {
            std::cout << "\n[Success] Авторизация успешна! Добро пожаловать, " << login << "." << std::endl;
            return 1;
        } else {
            std::cout << "[Error] Неверный логин или пароль. Попробуйте снова." << std::endl;
            return 0;
        }
    } 
    catch (const std::invalid_argument& e) {
        std::cout << "[Ошибка ввода] " << e.what() << std::endl;
        return 0; // Возвращаем 0, чтобы меню перерисовалось
    }
    catch (const std::exception& e) {
        std::cout << "[Критическая ошибка] " << e.what() << std::endl;
        return 0;
    }
}

bool LoginMenu::start() {
    while (true) {
        int result = inputCommand();
        if (result == -1) {
            std::cout << "Завершение работы программы." << std::endl;
            return false;
        } else if (result == 1) {
            UserMenu userMenu;
            userMenu.start();
        } else if (result == 2) {
            // <-- ЗАПУСК ADMIN MENU
            AdminMenu adminMenu;
            adminMenu.start();
        }
    }
}

} // namespace XXX