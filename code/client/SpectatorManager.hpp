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
    SpectatorManager(int port, char* adress, App* my_app);

};


#endif //PROJET_SPECTATORMANAGER_HPP
