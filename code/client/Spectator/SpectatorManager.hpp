//
//

#ifndef PROJET_SPECTATORMANAGER_HPP
#define PROJET_SPECTATORMANAGER_HPP


#include <vector>
#include "../NetworkedManager.hpp"
#include "../../common/Strings.hpp"
#include "../Game/GameInfo.hpp"
#include "../Main/MainManager.hpp"
//#include "../Game/GameManager.hpp"
#include "SpectatorUI.hpp"

class SpectatorUI;

class SpectatorManager : public NetworkedManager{
private:

    std::vector<GameInfo> allGames;
    SpectatorUI *spectatorUI;

    void getGamesFromMatchMaker();
    void parse_message_from_server(const std::string& message);

public:
    SpectatorManager(int port, App* master_app);

    void run() override ;

    int createGameInfo(const std::string& message, int& i);

    void goToMainMenu();

    ~SpectatorManager();

    void connectToGame(int&, std::string&);
};


#endif //PROJET_SPECTATORMANAGER_HPP
