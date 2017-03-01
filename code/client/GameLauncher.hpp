#ifndef GAMELAUNCHER_HPP
#define GAMELAUNCHER_HPP

#include <string>
#include "../common/Networking.h"
#include "NetworkedManager.hpp"
#include "../server/MatchMaker.hpp"

class GameLauncher : public NetworkedManager {

private:

    int player_id;
    std::string player_name;
    std::string mode;


public:
    GameLauncher(int port, char* address, int id, std::string name, App* app, std::string _mode);
    void sendJoinRequest();
    void run() override;
};

#endif