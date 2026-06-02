// CMenu.h
#pragma once
#include <string>
#include <cstddef>
#include <map>
#include "../models/headers/Cmd.h"

namespace XXX {
class CMenu {
public:
    std::string getTitle();
    size_t getCount();
    virtual void print() = 0;
    int inputCommand();
    CMenu();
    virtual bool start() = 0;
    
    // Метод очистки экрана
    int clearScreen();

protected:
    std::string select;
    size_t count;
    std::string title;
    std::map<std::string, Cmd> commands;
};
}