#include <iostream>
#include "UpdateStatsCommand.hpp"

int UpdateStatsCommand::getPlayerId() {
    return playerId;
}

int UpdateStatsCommand::getPnjKilled() {
    return pnjKilled;
}

bool UpdateStatsCommand::getIsWinner() {
    return isWinner;
}

void UpdateStatsCommand::parse(char *data) {
    /*
     * The format of the command is "Update,<PlayerID>,<PNJKilled>,<isWinner>;"
     * Example: "Update,12,4,false;"
     */
    std::cout << "Pasing stats" << std::endl;
    Command::parse(data); // Parses the action
    playerId = std::stoi(getNextToken());
    pnjKilled = std::stoi(getNextToken());
    isWinner = stringToBool(getNextToken());
}

