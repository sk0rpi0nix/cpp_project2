#include "headers/Message.h"

namespace XXX {
Message::Message(int id, const std::string& sender, const std::string& receiver, const std::string& text)
    : id(id), senderName(sender), receiverName(receiver), text(text) {}

std::ostream& operator<<(std::ostream& os, const Message& msg) {
    os << "[" << msg.id << "] " << msg.senderName << " -> " << msg.receiverName << ": " << msg.text;
    return os;
}
}