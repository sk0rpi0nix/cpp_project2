#include<iostream>
#include<string>
#include"headers/Message.h"
 

namespace human {
        Message::Message(int id, int userId, std::string text) {
            this->id = id;
            this->userId = userId;
            this->text = text;
        }
    
        void Message::printMessage() {
            std::cout << userId << ":" << text << std::endl;
        }

}
