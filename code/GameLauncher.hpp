#ifndef GAMELAUNCHER_HPP
#define GAMELAUNCHER_HPP

#include <string>
#include "Networking.h"
#include "Manager.hpp"
#include "MatchMaker.hpp" // Vraiment moche, j'utilise juste parce que j'ai besoin du GAME_START_STRING
// TODO: faudra probablement faire un fichier qui reprend tous les strings

class GameLauncher : Manager {


public:
    GameLauncher(int port, char* address);
    void sendJoinRequest(std::string mode);
};

#endif