#include "GameConsoleUI.hpp"

#include "../../common/Other/Tools.hpp"


GameConsoleUI::GameConsoleUI(bool isSupporter, unsigned seed, GameManager *manager) : GameUI(isSupporter, seed,
                                                                                             manager) {}

/* Ask the user the coordinates of the tower to place it*/
Position GameConsoleUI::getPosBuyingTower() {
    int x;
    int y;

    do {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Enter the coordinates of the place where you want to put the tower" << std::endl;
        std::cout << "X: ";
        std::cin >> x;
        std::cout << "Y: ";
        std::cin >> y;
    } while (!checkCoord(x, y));

    return Position(x, y);
}

/*Check the coordinates that the user has enter to place, delete or upgrade a tower*/
bool GameConsoleUI::checkCoord(int x, int y) {
    if (0 <= x and x < SIZE and 0 <= y and y < SIZE) {
        return true;
    }
    std::cout << "Enter an X and a Y between 0 and " << SIZE - 1 << std::endl;
    return false;
}

/*Display the map*/
void GameConsoleUI::display(GameState &gameState, int quadrant) {

    map->display(gameState, quadrant);
}

/*Ask the user the coordinates of the tower to sell it*/
Position GameConsoleUI::getPosSellingTower() {
    int x;
    int y;

    do {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Enter the coordinates of the tower that you want to sell" << std::endl;
        std::cout << "X: ";
        std::cin >> x;
        std::cout << "Y: ";
        std::cin >> y;
    } while (!checkCoord(x, y));

    return Position(x, y);
}

/*Ask the user the coordinates of the tower to upgrade it*/
Position GameConsoleUI::getPosUpgradeTower() {
    int x;
    int y;

    do {
        std::cin.clear();
        std::cin.ignore();
        std::cout << "Enter the coordinates of the tower that you want to upgrade" << std::endl;
        std::cout << "X: ";
        std::cin >> x;
        std::cout << "Y: ";
        std::cin >> y;
    } while (!checkCoord(x, y));

    return Position(x, y);
}

/*Display the player info*/
void GameConsoleUI::displayPlayerInfos(GameState &gameState, int quadrant) {
    if (!isSupporter()) {
        if (manager->isAlive()) {
            displayCurrentPlayerInfo(gameState, quadrant);
        } else {
            displayDeadMessage();
        }
    } else {
        displayInfoForSupporter(gameState, 0);
    }
}

/*Display the current information of a player during the game*/
void GameConsoleUI::displayCurrentPlayerInfo(GameState &gameState, int quadrant) {
    int gold = gameState.getPlayerStates()[quadrant].getMoney();
    int pnj_killed = gameState.getPlayerStates()[quadrant].getPnjKilled();
    int hp = gameState.getPlayerStates()[quadrant].getHp();
    bool isSupported = gameState.getPlayerStates()[quadrant].getIsSupported();

    std::string infos = "Money: " + std::to_string(gold) + " $ " + "\tNPC killed: " + std::to_string(pnj_killed)
                        + "\nHP: " + std::to_string(hp) + "\tSupported: " + bool_to_string(isSupported) +
                        "\t Quadrant: " + QUADRANT_NAMES[quadrant];

    std::cout << std::endl << infos << std::endl;
    std::cout << std::endl;
}

/*Display the current information of all players in the supporter mode*/
void GameConsoleUI::displayInfoForSupporter(GameState &gameState, int quadrant) {
    std::string infos;
    int i = 0;
    for (PlayerState &ps : gameState.getPlayerStates()) {
        infos += ps.getUsername() + " - Money : " + std::to_string(ps.getMoney()) + " $ " +
                 "\tNPC killed: " + std::to_string(ps.getPnjKilled()) + "\tHP: " + std::to_string(ps.getHp())
                 + "\t Quadrant: " + QUADRANT_NAMES[i] + "\n";

        i++;
    }

    std::cout << std::endl << infos << std::endl;
    std::cout << std::endl;
}

/*Display the action */
void GameConsoleUI::displayPosingPhase() {
    std::cout << "You can: " << std::endl;
    std::cout << "1. Buy tower " << std::endl;
    std::cout << "2. Sell tower " << std::endl;
    std::cout << "3. Upgrade tower " << std::endl;
    std::cout << "4. Send a predefined message" << std::endl;
    std::cout << std::endl;
}

void GameConsoleUI::displayTowerShop() {
    std::cout << "You can choose among the following towers: " << std::endl;
    std::cout << "1. GunTower : " << std::to_string(GUN_TOWER_PRICE) << " $ " << std::endl;
    std::cout << "2. SniperTower : " << std::to_string(SNIPER_TOWER_PRICE) << " $ " << std::endl;
    std::cout << "3. ShockTower : " << std::to_string(SHOCK_TOWER_PRICE) << " $ " << std::endl;
    std::cout << "4. MissileTower : " << std::to_string(MISSILE_TOWER_PRICE) << " $ " << std::endl;
    std::cout << std::endl;
}

/* Ask at the user his choice */
int GameConsoleUI::getChoice(int maxValue) {
    int x = -1;
    std::cout << "   Enter your choice: ";
    std::cin >> x;
    while (std::cin.fail() or x < 1 or x > maxValue) {
        std::cout << "   Error, enter a integer between 1 and " << maxValue << std::endl;
        std::cout << "   Enter your choice: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> x;
    }
    return x;
}

void GameConsoleUI::displayGameOverAndStats(GameState &gamestate) {

    Drawing::drawWhiteHouse("END GAME STATS");

    for (auto &player : gamestate.getPlayerStates()) {

        std::cout << "   " << "Username : " + player.getUsername() << " | NPC killed : "
                  << player.getPnjKilled() << " ";

        std::string winner_or_loser = player.getIsWinner() ? "| WINNER" : "| LOSER";
        std::cout << winner_or_loser << std::endl;
    }

    // TODO: show stats

    std::cout << "\nPress Enter to come back in the main menu..." << std::endl;
    std::cin.ignore().get();

    manager->comeBackToMenu();
}


void GameConsoleUI::displayDeadMessage() {
    std::cout << "You are dead. You can now watch the game peacefully" << std::endl;
}

void GameConsoleUI::displayPlayersPlacingTowersMessage() {
    std::cout << "Please wait. The remaining players are placing towers" << std::endl;
}

int GameConsoleUI::getTowerTypeChoice() {
    displayTowerShop();
    return getChoice(NB_OF_TYPE_OF_TOWER);
}

Position GameConsoleUI::getPositionOfTowerPlacement() {
    display(manager->getGameState(), manager->getQuadrant());
    displayPlayerInfos(manager->getGameState(), manager->getQuadrant());
    return getPosBuyingTower();
}

void GameConsoleUI::placeTowerAction() {
    int towerChoice = getTowerTypeChoice();
    Position towerPos = getPositionOfTowerPlacement();
    if (towerChoice == 1) {
        manager->placeGunTower(towerPos);
    } else if (towerChoice == 2) {
        manager->placeSniperTower(towerPos);
    } else if (towerChoice == 3) {
        manager->placeShockTower(towerPos);
    } else {
        manager->placeMissileTower(towerPos);
    }
}

void GameConsoleUI::sellTowerAction() {
    Position toSell = getPosSellingTower();
    manager->sellTower(toSell);
}

void GameConsoleUI::upgradeTower() {
    Position toUpgrade = getPosUpgradeTower();
    manager->upgradeTower(toUpgrade);
}

void *GameConsoleUI::input_thread() {

    while (1) {
        displayPosingPhase();
        int choice = getChoice(4);
        std::cout << "Choice: " << choice << std::endl;
        display(manager->getGameState(), manager->getQuadrant());
        displayPlayerInfos(manager->getGameState(), manager->getQuadrant());

        if (choice == 1) {
            placeTowerAction();
        } else if (choice == 2) {
            sellTowerAction();
        } else if (choice == 3) {
            upgradeTower();
        } else {
            sendPredefinedMessage();
        }
        display(manager->getGameState(), manager->getQuadrant());
        displayPlayerInfos(manager->getGameState(), manager->getQuadrant());
    }
}


void *GameConsoleUI::staticInputThread(void *self) {
    return dynamic_cast<GameConsoleUI *>(static_cast<GameUI *>(self))->input_thread();
}

void GameConsoleUI::addChatMessage(const std::string &message, const std::string &sender) {
    // TODO: c'est juste pour tester, faudra faire la vraie fonction apres
    std::cout << std::endl << sender << ": " << message << std::endl;
}

void GameConsoleUI::disableNukeSpell() {};

void GameConsoleUI::enableNukeSpell() {}

void GameConsoleUI::sendPredefinedMessage() {
    displayPredefinedMessages();
    int choice = getChoice(3);
    manager->sendMessageToPlayers(MESSAGES[choice - 1]);
}

void GameConsoleUI::displayPredefinedMessages() {
    std::cout << "Send the messages: " << std::endl;
    std::cout << "1. " << MESSAGES[0] << std::endl;
    std::cout << "2. " << MESSAGES[1] << std::endl;
    std::cout << "3. " << MESSAGES[2] << std::endl;
    std::cout << std::endl;
}

void GameConsoleUI::disableFreezeSpell() {

}

void GameConsoleUI::enableFreezeSpell() {

};

void GameConsoleUI::disableAirStrike() {

}

void GameConsoleUI::enableSpells() {}

void GameConsoleUI::disableSpells() {}

void GameConsoleUI::handlePlaceTowerPhaseStart() {
    if (manager->isAlive() && !isSupporter()) {
        inputThread = pthread_create(&thr, NULL, &GameConsoleUI::staticInputThread, this);
    } else {
        // TODO: Decouvrir pourquoi est-ce qu'il y a ce display
        display(manager->getGameState(), manager->getQuadrant());

        if (isSupporter()) {
            displayPlayersPlacingTowersMessage();
        } else {
            displayDeadMessage();
        }
    }
}

void GameConsoleUI::handleWaveStart() {
    if (!isSupporter()) {
        inputThread = pthread_cancel(thr);
    }
}


void GameConsoleUI::adPopUp() {}


