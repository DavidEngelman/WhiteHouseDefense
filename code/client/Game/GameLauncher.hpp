#ifndef GAMELAUNCHER_HPP
#define GAMELAUNCHER_HPP

#include <string>
#include "../../common/Networking.hpp"
#include "../NetworkedManager.hpp"
#include "../../server/MatchMaker.hpp"

class GameLauncher : public NetworkedManager {

private:

    std::string mode;


public:
    GameLauncher(int port, App* app, std::string _mode);
    void sendJoinRequest();
    void run() override;

    void leaveQueue();

    void launchGame();
};

#endif