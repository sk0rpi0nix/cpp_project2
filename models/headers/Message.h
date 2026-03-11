#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

namespace human {


class Message {
    private:
        int id;
        int userId;
        std::string text;

    public:
        Message(int id, int userId, std::string text);

        void printMessage();
    };

}

#endif