#pragma once

#include <string>

using namespace std;


namespace XXX {
    class CMenuItem {
    public:
        typedef int(*Func)();
        Func func{};
        string item_name{};
        string getName();
        void print();
        int run();
        
        CMenuItem(std::string, Func);
    };
}