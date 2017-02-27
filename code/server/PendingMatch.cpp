#include "PendingMatch.h"

// TODO: bien reflechir à ce qu'on garde comme information dans le std::vector
// Choisir et puis écrire pourquoi on a choisi ça

PendingMatch::PendingMatch(std::string modeName) : mode(modeName) {}

const std::string &PendingMatch::getMode() const {
    return mode;
}

std::vector<PlayerConnection> &PendingMatch::getPlayerConnections() const {
    return playerConnections;
}

void PendingMatch::add_player_to_queue(PlayerConnection& playerConnection) {
    playerConnections.push_back(playerConnection);
}

void PendingMatch::remove_player_from_queue(PlayerConnection& playerConnection) {
    playerConnections.erase(std::remove(playerConnections.begin(), playerConnections.end(), playerConnection));
}
//TODO: Cette method marche pas

void PendingMatch::clear() {
    playerConnections.clear();
}

bool PendingMatch::is_full(){
    return (playerConnections.size() == MAX_SIZE);
}