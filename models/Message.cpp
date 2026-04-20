#include<iostream>
#include<string>
#include"headers/Message.h"
 

namespace XXX {
        Message::Message(int id, int userId, std::string text) {
            this->id = id;
            this->userId = userId;
            this->text = text;
        }
    
        void Message::printMessage() {
            std::cout << id << "-" << userId << ":" << text << std::endl;
        }


        // Дружественная функция вывода для Message
        std::ostream& operator<<(std::ostream& os, const Message& msg) {
            os << "Message{id=" << msg.id << ", userId=" << msg.userId << ", text=\"" << msg.text << "\"}";
            return os;
        }

}
