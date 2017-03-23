#include "Message.hpp"


Message::Message(char delimiter) : delimiter(delimiter), _hasReachedEnd(false), currentPosInBuffer(0), buffer(nullptr) {

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
    while ((buffer[currentPosInBuffer] != delimiter) &&
           (buffer[currentPosInBuffer] != ';') &&
           (buffer[currentPosInBuffer] != '\0')) {
        token += buffer[currentPosInBuffer];
        currentPosInBuffer++;
    }

    // We reached the delimiter
    _hasReachedEnd = (buffer[currentPosInBuffer] == ';' or buffer[currentPosInBuffer] == '\0');

    currentPosInBuffer++;
    return token;
}

int Message::getNextInt() {
    const std::string &token = getNextToken();
    return std::stoi(token);
}

std::string Message::getTokenWithSize(int size){
    std::string token;
    int numRead = 0;
    while ((buffer[currentPosInBuffer] != '\0') && numRead < size) {
        token += buffer[currentPosInBuffer];
        currentPosInBuffer++;
        numRead += 1;
    }

    currentPosInBuffer++; // There should be a delimiter next
    _hasReachedEnd = (buffer[currentPosInBuffer] == ';' or buffer[currentPosInBuffer] == '\0');

    currentPosInBuffer++;
    return token;
}

bool Message::hasReachedEnd() {
    return _hasReachedEnd;
}

std::string Message::getRemainingContent(){
    std::string token;
    while ((buffer[currentPosInBuffer] != ';') &&
           (buffer[currentPosInBuffer] != '\0')) {
        token += buffer[currentPosInBuffer];
        currentPosInBuffer++;
    }

    // We reached the delimiter
    _hasReachedEnd = true;

    currentPosInBuffer++;
    return token;
}