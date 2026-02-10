#include <iostream>
#include <string>
#include "menu/CMenu.h"
#include "menu/CMenuItem.h"

using namespace std;
using namespace XXX;


#pragma region функции-заглушки
int f1() {
    std::cout << "  -----\n /     \\\n|  O O  |\n|   ^   |\n \\  -  /\n  -----\n\n";
    return 1;
}

int f2() {
    const int a = 5,b = 3;

    std::cout << "a * b is "<< a*b<<"\n\n";
    return 2;
}

int f3() {
    std::cout << "This function does completely nothing ^o^\n\n";
    return 3;
}
#pragma endregion

const int ITEMS_NUMBER = 3;


int main() {
    
    CMenuItem items[ITEMS_NUMBER] {CMenuItem{"first item", f1}, CMenuItem{"second item", f2}, CMenuItem{"third item", f3}};
    CMenu menu("My console menu", items, ITEMS_NUMBER);
    while (menu.runCommand()) {};

    return 0;
}