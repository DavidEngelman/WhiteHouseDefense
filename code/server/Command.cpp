#include "Command.hpp"

Command::Command(): _hasReachedEnd(false), currentPosInBuffer(0), buffer(nullptr) {

}

std::string Command::getAction() const {
    return action;
}


void Command::parse(char *data) {
    buffer = data;
    currentPosInBuffer = 0;

    extract_action(data);
}

/*
 * Method that can be called after parse. Parse extract the action, and this method
 * allows you to extract any additional strings in the command.
 */
std::string Command::getNextToken() {
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

bool Command::hasReachedEnd() {
    return _hasReachedEnd;
}

int Command::extract_action(char *data) {
    setData(data); // For compatibility with subclasses
    // TODO: adapt subclasses to use new capacities.
    action = getNextToken();
    return currentPosInBuffer;
}

void Command::setData(char *data) { buffer = data; }
