//
//

#ifndef PROJET_SPECTATORMANAGER_HPP
#define PROJET_SPECTATORMANAGER_HPP


#include "NetworkedManager.hpp"
#include "SpectatorUI.hpp"
#include "../common/Strings.hpp"

typedef struct GameInfo{
    int port;
    std::string gameMode;
    std::string players;

}GameInfo;

class SpectatorManager : public NetworkedManager{
private:

    SpectatorUI spectatorUI;
    void getGamesFromMatchMaker();
    std::string parse_message_from_server(std::string message);

public:
    SpectatorManager(int port, char* address, int id, std::string username, App* master_app);

    void run() override ;
};


#endif //PROJET_SPECTATORMANAGER_HPP
