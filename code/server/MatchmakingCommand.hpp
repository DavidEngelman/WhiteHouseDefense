#ifndef PROJET_MATCHMAKINGCOMMAND_HPP
#define PROJET_MATCHMAKINGCOMMAND_HPP


#include "Command.hpp"
#include "PendingMatch.h"

class MatchmakingCommand : Command {
private:

    PlayerConnection playerConnection;
    std::string mode;

public:

    MatchmakingCommand() = delete;
    MatchmakingCommand(int socket_fd): Command() {
        playerConnection.setSocket_fd(socket_fd);
    }

    ~MatchmakingCommand() = default;

    void parse(char* data) override;

    const PlayerConnection getPlayerConnection() const;

    const std::string getMode() const;

};


#endif //PROJET_MATCHMAKINGCOMMAND_HPP
