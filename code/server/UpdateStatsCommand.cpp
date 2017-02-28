//
//

#include "UpdateStatsCommand.h"

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
    std::string id, pnjKilled, isWinner;

    int i = extract_action(data);

    while (data[i] != ',') {

        id += data[i];
        i++;
    }
    i++;

    // Extracts pnjKilled
    while (data[i] != ',') {

        pnjKilled += data[i];
        i++;
    }
    i++;

    // Extracts isWinner
    while (data[i] != ';') {

        isWinner += data[i];
        i++;
    }
    i++; // passe la virgule

    playerId = stoi(id);
    pnjKilled = stoi(pnjKilled);
    isWinner = stringToBool(isWinner);

}

bool UpdateStatsCommand::stringToBool(std::string str) {
    if (str == "true")
        return true;
    else
        return false;
}