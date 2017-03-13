#include "Message.hpp"


Message::Message(): _hasReachedEnd(false), currentPosInBuffer(0), buffer(nullptr) {

}

void Message::setData(char *data) {
    buffer = data;
    currentPosInBuffer = 0;
}

/*
 * Method that can be called after parse. Parse extract the action, and this method
 * allows you to extract any additional strings in the command.
 */
std::string Message::getNextToken() {
    std::string token;
    while ((buffer[currentPosInBuffer] != ',') && (buffer[currentPosInBuffer] != ';')) {
        token += buffer[currentPosInBuffer];
        currentPosInBuffer++;
    }

    // We reached the delimiter
    _hasReachedEnd = (buffer[currentPosInBuffer] == ';');

    currentPosInBuffer++;
    return token;
}

bool Message::hasReachedEnd() {
    return _hasReachedEnd;
}