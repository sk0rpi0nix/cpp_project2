#include "headers/Cmd.h"
using namespace std;

namespace XXX {
Cmd::Cmd() : name(""), command(nullptr), desc("") {}

// ИСПРАВЛЕНО: реализация конструктора с тремя аргументами
Cmd::Cmd(string n, cmdFunc func, string d) : name(n), command(func), desc(d) {
}

int Cmd::exec(const string& args) {
    if (command != nullptr) {
        return command(args);
    }
    return 0;
}

string Cmd::getName() {
    return name;
}

string Cmd::getDesc() {
    return desc;
}
}