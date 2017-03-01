//
//

#ifndef PROJET_SPECTATORMANAGER_HPP
#define PROJET_SPECTATORMANAGER_HPP


#include "NetworkedManager.hpp"
#include "SpectatorUI.hpp"
#include "../common/Strings.hpp"

class SpectatorManager : public NetworkedManager{
private:

    SpectatorUI spectatorManagerUI;
    void getGamesFromMatchMaker();

public:
    SpectatorManager(int port, char* address, int id, std::string username, App* master_app);

    void run() override ;
};


#endif //PROJET_SPECTATORMANAGER_HPP
