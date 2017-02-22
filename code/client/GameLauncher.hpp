#ifndef GAMELAUNCHER_HPP
#define GAMELAUNCHER_HPP

#include <string>
#include "../common/Networking.h"
#include "NetworkedManager.hpp"
#include "../server/MatchMaker.hpp"
// TODO: faudra probablement faire un fichier qui reprend tous les strings

class GameLauncher : public NetworkedManager {

private:

    int player_id;


public:
    GameLauncher(int port, char* address, int id, App* app);
    void sendJoinRequest(std::string mode);
    void run() override;
};

#endif