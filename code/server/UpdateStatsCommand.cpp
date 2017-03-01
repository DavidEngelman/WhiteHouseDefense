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
    std::string id, pnj_killed, is_winner;

    int i = extract_action(data);

    while (data[i] != ',') {

        id += data[i];
        i++;
    }
    i++;

    // Extracts pnjKilled
    while (data[i] != ',') {

        pnj_killed += data[i];
        i++;
    }
    i++;

    // Extracts isWinner
    while (data[i] != ';') {

        is_winner += data[i];
        i++;
    }
    i++; // passe la virgule

    playerId = stoi(id);
    pnjKilled = stoi(pnj_killed);
    isWinner = stringToBool(is_winner);

}

