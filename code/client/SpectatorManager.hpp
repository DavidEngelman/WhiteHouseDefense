//
//

#ifndef PROJET_SPECTATORMANAGER_HPP
#define PROJET_SPECTATORMANAGER_HPP


#include <vector>
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
    std::vector<GameInfo> allGames;
    SpectatorUI spectatorUI;
    void getGamesFromMatchMaker();
    void parse_message_from_server(const std::string& message);

public:
    SpectatorManager(int port, char* address, int id, std::string username, App* master_app);

    void run() override ;

    int createGameInfo(const std::string& message, int& i);
};


#endif //PROJET_SPECTATORMANAGER_HPP
