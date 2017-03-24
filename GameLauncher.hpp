#ifndef GAMELAUNCHER_HPP
#define GAMELAUNCHER_HPP

#include <string>
#include "code/client/Other/NetworkedManager.hpp"

class GameLauncher : public NetworkedManager {

private:

    std::string mode;


public:
    GameLauncher(int port, App* app, std::string _mode);
    void sendJoinRequest();
    void run() override;
};

#endif
