#include "MatchmakingCommand.hpp"

void MatchmakingCommand::parse(char *data) {
    /*
     * La commande suit le format suivant "<Mode>,<PlayerID>,<Username>"
     * Exemple: "classic,17,bob"
     */
    Command::setData(data); // Pour qu'on puisse utiliser getNextToken();
    mode = getNextToken();
    playerConnection.setPlayer_id(std::stoi(getNextToken()));
    playerConnection.setUsername(getNextToken());
}

const PlayerConnection MatchmakingCommand::getPlayerConnection() const {
    return playerConnection;
};

const std::string MatchmakingCommand::getMode() const {
    return mode;
};


