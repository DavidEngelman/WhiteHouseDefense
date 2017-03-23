#ifndef PROJET_SPECTATORMANAGER_HPP
#define PROJET_SPECTATORMANAGER_HPP


#include <vector>
#include "../Other/NetworkedManager.hpp"
#include "../../common/Other/Strings.hpp"
#include "../Game/GameInfo.hpp"
#include "../Main/MainManager.hpp"
#include "../Game/GameManager.hpp"
#include "SpectatorUI.hpp"

class SpectatorUI;

class SpectatorManager : public NetworkedManager {
private:
    std::vector<GameInfo> allGames;
    SpectatorUI *spectatorUI;


    void parse_message_from_server(const std::string &message);

public:
    SpectatorManager(int port, App *master_app, bool fromFriendList = false);

    ~SpectatorManager();

    void run() override;

    void goToMainMenu();

    void connectToGame(GameInfo &, std::string &);

    int parseGameInfoAndAddToGames(const std::string &message, int &i);

    std::vector<GameInfo> getGames();

    void getGamesFromMatchMaker();

};


#endif //PROJET_SPECTATORMANAGER_HPP
