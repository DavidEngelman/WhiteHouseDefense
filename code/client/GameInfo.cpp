//
//

#include "GameInfo.h"

void GameInfo::print() {
    std::cout <<  "Mode: " << gameMode << " - Players: ";
    for (std::string& player : players){
        std::cout << player << " | ";
    }
    std::cout << std::endl;

}

int GameInfo::getPort() {
    return port;
}

std::string &GameInfo::getGameMode() {
    return gameMode;
}

std::vector<std::string> &GameInfo::getPlayers() {
    return players;
}

void GameInfo::setPort(int port) {
    GameInfo::port = port;
}

void GameInfo::setGameMode(const std::string &gameMode) {
    GameInfo::gameMode = gameMode;
}

void GameInfo::setPlayers(const std::vector<std::string> &players) {
    GameInfo::players = players;
}
