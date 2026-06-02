#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <iostream>

namespace XXX {
class Message {
public:
    int id;
    std::string senderName;
    std::string receiverName;
    std::string text;

    // Обновленный конструктор
    Message(int id, const std::string& sender, const std::string& receiver, const std::string& text);
    
    friend std::ostream& operator<<(std::ostream& os, const Message& msg);
};

// Функтор для сортировки (C++98 совместимый)
struct CompareMsgById {
    bool operator()(const Message& a, const Message& b) const {
        return a.id < b.id;
    }
};
}
#endif