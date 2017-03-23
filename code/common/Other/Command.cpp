#include "Command.hpp"

Command::Command() : Message(), action("Not Initialized") {

}

std::string Command::getAction() const {
    return action;
}

void Command::parse(char *data) {
    setData(data);
    extractAction(data);
}

int Command::extractAction(char *data) {
    setData(data); // For compatibility with subclasses
    // TODO: adapt subclasses to use new capacities.
    action = getNextToken();
    return currentPosInBuffer;
}
