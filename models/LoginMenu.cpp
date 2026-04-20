#include "headers/LoginMenu.h"
#include <iostream>

#include "headers/Storage.h"
#include "../menu/CMenu.h" // Подключаем реализацию MainMenu, если она есть

namespace XXX {

    LoginMenu::LoginMenu(CMenu* mainMenu) : mainMenuPtr(mainMenu) {
        // При создании меню сразу пытаемся загрузить базу
        // Если файла нет, база будет пустой, и войти нельзя
        loadUsersFromFile("users_db.txt");
    }

    bool LoginMenu::loadUsersFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "[Warning] Файл базы пользователей '" << filename << "' не найден. Создайте его или добавьте пользователей." << std::endl;
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            std::istringstream iss(line);
            std::string login, password;
            
            // Предполагаем формат файла: "login password"
            if (iss >> login >> password) {
                usersCreds[login] = password;
            }
        }
        
        file.close();
        std::cout << "[Info] Загружено пользователей: " << usersCreds.size() << std::endl;
        return true;
    }

    bool LoginMenu::validateCredentials(const std::string& login, const std::string& password) {
        auto it = usersCreds.find(login);
        
        // if (login == "admin" && password == "admin123") return true;
        // Если логин найден И пароль совпадает
        if (it != usersCreds.end() && it->second == password) {
            return true;
        }
        return false;
    }

    bool LoginMenu::start() {
        for (auto pair : usersCreds) {
            std::cout << pair.first << " " << pair.second << endl;  
        }

        std::string inputLogin, inputPassword;
        bool isAuthorized = false;

        std::cout << "\n=== СИСТЕМА АВТОРИЗАЦИИ ===" << std::endl;

        while (!isAuthorized) {
            std::cout << "Введите логин: ";
            if (!(std::cin >> inputLogin)) {
                continue;
            }

            std::cout << "Введите пароль: ";
            if (!(std::cin >> inputPassword)) {
                continue;
            }

            if (validateCredentials(inputLogin, inputPassword)) {
                std::cout << "\n[Success] Авторизация успешна! Добро пожаловать, " << inputLogin << "." << std::endl;
                isAuthorized = true;
            } else {
                std::cout << "[Error] Неверный логин или пароль. Попробуйте снова." << std::endl;
            }
        }

        // После выхода из цикла (успешная авторизация)
        // Запускаем главное меню
        if (mainMenuPtr != nullptr) {
            while (mainMenuPtr->runCommandLine()) {
                
            }
        } else {
            std::cerr << "[Error] Главное меню не инициализировано." << std::endl;
        }
        return false;
    }
}

