//
// Created by jurgen on 2/18/17.
//

#include "FriendListCommand.h"

void FriendListCommand::parse(char *data) {

    int i = extract_action(data);
    while (data[i] != ',' && data[i] != ';') {
        requester += data[i];
        i++;
    }
    if (data[i] == ',') {
        i++;

        while (data[i] != ',' && data[i] != ';') {
            receiver += data[i];
            i++;
        }
    }
}

std::string FriendListCommand::getRequester() {
    return requester;
}

std::string FriendListCommand::getReceiver() {
    return receiver;
}