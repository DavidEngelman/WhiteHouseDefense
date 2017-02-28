
#include "MainManager.hpp"
#include "GameLauncher.hpp"
#include "ProfileManager.hpp"
#include "RankingManager.hpp"
#include "FriendListManager.hpp"

const static std::string gameModes[3] = {CLASSIC_MODE, TEAM_MODE, TIMED_MODE};

MainManager::MainManager(char* ip_addr, int id, std::string username, App* my_app) :
    AbstractManager(ip_addr, my_app), player_id(id), username(username){}

void MainManager::run() {
    mainUI.display();
    switch (mainUI.select()) {
        case 1: {
            mainUI.displayGameModes();

            // TODO: mainUI.selectGameMode() renvoie un entier, alors qu'à cause du nom il semble
            // qu'il envoie un mode de jeu. Faut corriger soit le nom, soit le return de la fonction
            // Ce code suppose que les modes le resultat de mainUI.selectGameMode() est entre 1 et 3
            std::string gameMode = gameModes[mainUI.selectGameMode() - 1];
            GameLauncher * game = new GameLauncher(5556, server_ip_address, player_id, username, master_app, gameMode);
            master_app->transition(game);
            break;
        }
        case 2: {
            ProfileManager * profile = new ProfileManager(5555, server_ip_address, player_id, username, master_app);
            master_app->transition(profile);
            break;
        }
        case 3: {
            FriendListManager * friendListManager = new FriendListManager(5555, server_ip_address, player_id, username, master_app);
            master_app->transition(friendListManager);
            break;
        }
        case 4: {
            RankingManager * rankingManager = new RankingManager(5555, server_ip_address, player_id, username, master_app);
            master_app->transition(rankingManager);
            break;
        }
        default: {
            std::cout << "Exit !" << std::endl;
            break;
        }
    }
}