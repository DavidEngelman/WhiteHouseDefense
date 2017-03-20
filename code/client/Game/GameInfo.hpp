//
//

#ifndef PROJET_GAMEINFO_H
#define PROJET_GAMEINFO_H

#include <string>
#include <vector>
#include <iostream>

class GameInfo{

private:
    int port;
    std::string gameMode;
    std::vector<std::string> players;
public:
    int getPort();

    std::string &getGameMode();

    std::vector<std::string> &getPlayers();

    void setPort(int port);

    void setGameMode(const std::string &gameMode);

    void setPlayers(const std::vector<std::string> &players);

    void print();

    bool isInPlayers(std::string player);
};

#endif //PROJET_GAMEINFO_H
