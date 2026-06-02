// CMenu.cpp
#include "CMenu.h"
#include <iostream>
#include <stdexcept>

namespace XXX {

std::string CMenu::getTitle() { return title; }
size_t CMenu::getCount() { return commands.size(); }

int CMenu::clearScreen() {
    // \033[2J clears the screen, \033[H moves the cursor to the top-left corner
    std::cout << "\033[2J\033[H" << std::flush;
    return 1;
}

int CMenu::inputCommand() {
    print();
    std::cout << "\n>> ";
    string line;
    getline(cin, line);
    
    if (line == "exit") {
        return -1;
    }

    size_t spacePos = line.find(' ');
    string command = line;
    string args = "";

    try {
        // Безопасное разделение строки
        if (spacePos != string::npos) {
            command = line.substr(0, spacePos);
            args = line.substr(spacePos + 1);
        }

        auto it = commands.find(command);
        if (it != commands.end()) {
            return it->second.exec(args);
        } else {
            if (!command.empty()) {
                cout << "[Ошибка] Неизвестная команда: '" << command << "'" << endl;
            }
        }
    } 
    // 2. Перехват исключений парсинга или выполнения команд
    catch (const std::out_of_range& e) {
        cerr << "[Системная ошибка] " << e.what() << endl;
    }
    catch (const std::invalid_argument& e) {
        cerr << "[Ошибка ввода] " << e.what() << endl;
    }
    catch (const std::exception& e) {
        cerr << "[Неизвестная ошибка] " << e.what() << endl;
    }
    
    return 0; // Возвращаем 0, чтобы цикл меню продолжился
}
CMenu::CMenu() : select(""), count(0), title("") {}

} // namespace XXX