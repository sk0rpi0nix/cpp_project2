#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>

namespace XXX {


class Message {
    private:
        int id;
        int userId;
        std::string text;

    public:
        Message(int id, int userId, std::string text);

        void printMessage();

        void printMessage() const;

        // Дружественная функция для вывода (по заданию перегрузка ввода не нужна)
        friend std::ostream& operator<<(std::ostream& os, const Message& msg);
    };

}

#endif