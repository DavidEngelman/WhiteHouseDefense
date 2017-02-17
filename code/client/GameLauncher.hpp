#ifndef GAMELAUNCHER_HPP
#define GAMELAUNCHER_HPP

#include <string>
#include "../common/Networking.h"
#include "Manager.hpp"
#include "../server/MatchMaker.hpp"
// TODO: faudra probablement faire un fichier qui reprend tous les strings

class GameLauncher : Manager {


public:
    GameLauncher(int port, char* address);
    void sendJoinRequest(std::string mode);
};

#endif