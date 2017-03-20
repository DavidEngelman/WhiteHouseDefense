//
// Created by jurgen on 2/18/17.
//

#ifndef PROJET_FRIENDLISTCOMMAND_H
#define PROJET_FRIENDLISTCOMMAND_H

#include <iostream>
#include "../common/Command.hpp"

class FriendListCommand: public Command {
private:
    std::string requester = "";
    std::string receiver = "";

public:

    FriendListCommand() = default;
    ~FriendListCommand() = default;
    
    void parse(char* data) override ;
    std::string getRequester();
    std::string getReceiver();
    
};


#endif //PROJET_FRIENDLISTCOMMAND_H