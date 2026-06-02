#ifndef CMD_H
#define CMD_H
using namespace std;
#include <string>

namespace XXX {
class Cmd {
public:
    // ИСПРАВЛЕНО: теперь принимаем const string&, как и в ваших меню
    typedef int (*cmdFunc)(const string&);
    
    Cmd();
    // ИСПРАВЛЕНО: добавлен третий аргумент d со значением по умолчанию ""
    Cmd(string n, cmdFunc func, string d = ""); 
    
    int exec(const string&);
    string getName();
    string getDesc();

private:
    string name;
    cmdFunc command;
    string desc;
};
}
#endif