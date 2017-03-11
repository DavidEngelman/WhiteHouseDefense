
#include "MainManager.hpp"
#include "../Game/GameLauncher.hpp"
#include "../Profile/ProfileManager.hpp"
#include "../Ranking/RankingManager.hpp"
#include "../FriendList/FriendListManager.hpp"
#include "../Spectator/SpectatorManager.hpp"
#include "MainGUI.hpp"

const static std::string gameModes[3] = {CLASSIC_MODE, TIMED_MODE, TEAM_MODE};

MainManager::MainManager(int port, App *my_app) :
        NetworkedManager(port, my_app), mainGUI(new MainGUI(this)) {}

void MainManager::run() {
    if(true) { //OUBLIEZ PAS DE REMETTRE isConsole
        int choice;
        mainUI.display();
        switch (mainUI.select()) {
            case 1: {
                mainUI.displayGameModes();
                choice = mainUI.selectGameModeInt();
                // Ce code suppose que le resultat de mainUI.selectGameMode() est entre 0 et 2

                if (choice != 3) {
                    std::string gameMode = gameModes[choice];
                    GameLauncher *game = new GameLauncher(5556, master_app, gameMode);
                    master_app->transition(game);
                } else {
                    run();
                }
                break;
            }
            case 2: {
                SpectatorManager *spectator = new SpectatorManager(5556, master_app);
                master_app->transition(spectator);
                break;
            }
            case 3: {
                ProfileManager *profile = new ProfileManager(5555, master_app);
                master_app->transition(profile);
                break;
            }
            case 4: {
                FriendListManager *friendListManager = new FriendListManager(5555, master_app);
                master_app->transition(friendListManager);
                break;
            }
            case 5: {
                RankingManager *rankingManager = new RankingManager(5555, master_app);
                master_app->transition(rankingManager);
                break;
            }
            default: {
                std::string message = "Exit," + std::to_string(master_app->get_id());
                send_message(server_socket, message.c_str());
                break;
            }
        }
    }
    else{
        mainGUI->setupGUI();
    }
}