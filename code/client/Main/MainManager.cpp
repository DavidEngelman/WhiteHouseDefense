
#include "MainManager.hpp"
#include "../Profile/ProfileManager.hpp"
#include "../Ranking/RankingManager.hpp"
#include "../FriendList/FriendListManager.hpp"
#include "../Spectator/SpectatorManager.hpp"
#include "MainGUI.hpp"
#include "MainConsoleUI.hpp"
#include "../Settings/SettingsManager.hpp"

const static std::string gameModes[3] = {CLASSIC_MODE, TEAM_MODE, TIMED_MODE};

MainManager::MainManager(int port, App *my_app) :
        NetworkedManager(port, my_app) {
    if (!isConsole) {
        std::cout << "Building GUI" << std::endl;
        mainUI = new MainGUI(this, master_app->getMainWindow());
        master_app->getMainWindow()->setFixedSize(1000,600);
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
        } case 2: {
            SpectatorManager *spectator = new SpectatorManager(MATCHMAKER_SERVER_PORT, master_app);
            master_app->transition(spectator);
            break;
        } case 3: {
            ProfileManager *profile = new ProfileManager(ACCOUNT_SERVER_PORT, master_app);
            master_app->transition(profile);
            break;
        } case 4: {
            if (!master_app->isFriendListActive()) {
                FriendListManager *friendListManager = new FriendListManager(ACCOUNT_SERVER_PORT, master_app);
                friendListManager->run();
            }
            break;
        } case 5: {
            RankingManager *rankingManager = new RankingManager(ACCOUNT_SERVER_PORT, master_app);
            master_app->transition(rankingManager);
            break;
        } case 6: {
            SettingsManager *settingsManager = new SettingsManager(ACCOUNT_SERVER_PORT, master_app);
            master_app->transition(settingsManager);
            break;
        } default: {
            break;
        }
    }
}

void MainManager::handleGameModeChoice() {
    int choice = mainUI->getGameModeChoice();
    // Ce code suppose que le resultat de mainUI.selectGameMode() est entre 0 et 2

    if (choice != 3) { /* Un des 3 modes de jeu */
        std::string gameMode = gameModes[choice];
        master_app->launchMatchmaking(gameMode);
        mainUI->showInQueue();
    } else { /* Retour au menu principal */
        run();
    }
}

bool MainManager::isInQueue() {
    return master_app->isInQueue();
}

void MainManager::leaveQueue() {
    master_app->leaveQueue();

}

MainManager::~MainManager() {
    mainUI->destroy();
}
