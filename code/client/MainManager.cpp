
#include "MainManager.hpp"
#include "GameLauncher.hpp"
#include "ProfileManager.hpp"
#include "RankingManager.hpp"
#include "FriendListManager.hpp"
#include "SpectatorManager.hpp"

const static std::string gameModes[3] = {CLASSIC_MODE, TIMED_MODE, TEAM_MODE};

MainManager::MainManager(int port, int id, std::string username, App* my_app) : NetworkedManager(port, my_app) {
    my_app->set_id(id);
    my_app->set_username(username);
}

MainManager::MainManager(App *my_app) : NetworkedManager(port, my_app) {}

void MainManager::run() {
    mainUI.display();
    switch (mainUI.select()) {
        case 1: {
            mainUI.displayGameModes();

            // Ce code suppose que les modes le resultat de mainUI.selectGameMode() est entre 0 et 2
            std::string gameMode = gameModes[mainUI.selectGameModeInt()];
            GameLauncher * game = new GameLauncher(5556, master_app, gameMode);
            master_app->transition(game);
            break;
        }
        case 2: {
            SpectatorManager * spectator = new SpectatorManager(5556, master_app);
            master_app->transition(spectator);
            break;
        }
        case 3: {
            ProfileManager * profile = new ProfileManager(5555, master_app);
            master_app->transition(profile);
            break;
        }
        case 4: {
            FriendListManager * friendListManager = new FriendListManager(5555, master_app);
            master_app->transition(friendListManager);
            break;
        }
        case 5: {
            RankingManager * rankingManager = new RankingManager(5555, master_app);
            master_app->transition(rankingManager);
            break;
        }
        default: {
            std::cout << "Exit !" << std::endl;

            std::string message = "Exit," + std::to_string(master_app->get_id());
            send_message(server_socket, message.c_str());
            break;
        }
    }
}