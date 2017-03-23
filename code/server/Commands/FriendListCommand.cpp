#include "FriendListCommand.hpp"

void FriendListCommand::parse(char *data) {
    /*
     * The format of the command is "<Action>,<Requester>;" or "<Action>,<Requester>,<Receiver>;"
     * Examples: "getProfileByUsername,bob"
     *           "addFriend,bob,alice"
     */
    Command::parse(data); // Parses the action
    requester = getNextToken(); // Always there
    if (!hasReachedEnd()){
        receiver = getNextToken();
    }
}

std::string FriendListCommand::getRequester() {
    return requester;
}

std::string FriendListCommand::getReceiver() {
    return receiver;
}