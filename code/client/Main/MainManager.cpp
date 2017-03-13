
#include "MainManager.hpp"
#include "../Game/GameLauncher.hpp"
#include "../Profile/ProfileManager.hpp"
#include "../Ranking/RankingManager.hpp"
#include "../FriendList/FriendListManager.hpp"
#include "../Spectator/SpectatorManager.hpp"
#include "MainGUI.hpp"
#include "MainConsoleUI.hpp"

const static std::string gameModes[3] = {CLASSIC_MODE, TIMED_MODE, TEAM_MODE};

MainManager::MainManager(int port, App *my_app) :
        NetworkedManager(port, my_app) {
    if (!isConsole) {
        mainUI = new MainGUI(this);
    } else {
        mainUI = new MainConsoleUI(this);
    }
}

void MainManager::run() {
    mainUI->display();
}

void MainManager::handleUserMenuChoice() {
    switch (mainUI->getMenuChoice()) {
        case 1: {
            mainUI->displayGameModesMenu();
            break;
        }
        case 2: {
            if (!isConsole) delete mainUI;
            SpectatorManager *spectator = new SpectatorManager(MATCHMAKER_SERVER_PORT, master_app);
            master_app->transition(spectator);
            break;
        }
        case 3: {
            if (!isConsole) delete mainUI;
            ProfileManager *profile = new ProfileManager(ACCOUNT_SERVER_PORT, master_app);
            master_app->transition(profile);
            break;
        }
        case 4: {
            if (!isConsole) delete mainUI;
            FriendListManager *friendListManager = new FriendListManager(ACCOUNT_SERVER_PORT, master_app);
            master_app->transition(friendListManager);
            break;
        }
        case 5: {
            if (!isConsole) delete mainUI;
            RankingManager *rankingManager = new RankingManager(ACCOUNT_SERVER_PORT, master_app);
            master_app->transition(rankingManager);
            break;
        }
        default: {
            std::string message = "Exit," + std::to_string(master_app->get_id());
            send_message(server_socket, message.c_str());
            if (!isConsole) delete mainUI;
            break;
        }
    }
}

void MainManager::handleGameModeChoice() {
    int choice = mainUI->getGameModeChoice();
    // Ce code suppose que le resultat de mainUI.selectGameMode() est entre 0 et 2

    if (choice != 3) { /* Un des 3 modes de jeu */
        std::string gameMode = gameModes[choice];
        GameLauncher *game = new GameLauncher(MATCHMAKER_SERVER_PORT, master_app, gameMode);
        master_app->transition(game);
    } else { /* Retour au menu principal */
        // TODO: close previous window
        run();
    }
}