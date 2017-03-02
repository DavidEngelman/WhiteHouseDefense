#include "GameUI.hpp"
#include <iostream>
#include "../common/Tools.hpp"


GameUI::GameUI(unsigned seed) : map(new Map(seed)) {}

Position GameUI::getPosBuyingTower() {
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

bool GameUI::checkCoord(int x, int y) {
    if (0 <= x and x < SIZE and 0 <= y and y < SIZE) {
        return true;
    }
    std::cout << "Enter an X and a Y between 0 and " << SIZE - 1 << std::endl;
    return false;
}

void GameUI::display(GameState& gameState, int quadrant) {
    map->display(gameState, quadrant);
}

Position GameUI::getPosSellingTower() {
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

void GameUI::displayPlayerInfos(GameState &gameState, int quadrant) {
    int gold = gameState.getPlayerStates()[quadrant].getMoney();
    int pnj_killed = gameState.getPlayerStates()[quadrant].getPnjKilled();
    int hp = gameState.getPlayerStates()[quadrant].getHp();
    bool isSupported = gameState.getPlayerStates()[quadrant].getIsSupported();

    std::string infos = "Money: " + std::to_string(gold) + "\tNPC killed: " + std::to_string(pnj_killed)
    +"\nHP: " + std::to_string(hp) + "\tSupported: " + bool_to_string(isSupported) +
    "\t Quadrant: " + QUADRANT_NAMES[quadrant];

    std::cout << std::endl << infos << std::endl;
    std::cout << std::endl;
}
void GameUI::displayPosingPhase() {

    std::cout << "You can: " << std::endl;
    std::cout << "1. Buy tower " << std::endl;
    std::cout << "2. Sell tower " << std::endl;
    std::cout << "3. Upgrade tower " << std::endl;
    std::cout << std::endl;

}
void GameUI::displayTowerShop() {
    std::cout << "You can choose among the following towers: " << std::endl;
    std::cout << "1. Attacktower " << std::endl;
    // put other tower types here
    std::cout << std::endl;
}

int GameUI::getChoice() {
    /* Ask at the user his choice */
    int x = -1;
    std::cout << "   Enter your choice: ";
    std::cin.clear();
    std::cin.ignore();
    std::cin >> x;
    while(std::cin.fail() or 0>x or x>3){
        std::cout << "   Error, enter a integer between 1 and 3 " << std::endl;
        std::cout << "   Enter your choice: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> x;
    }
    return x;
}

void GameUI::displayGameOver(GameState &gamestate) {

    Drawing::drawWhiteHouse("END GAME STATS");

    for (auto& player : gamestate.getPlayerStates()) {

        std::cout << "   " << "Username : " + player.getUsername() <<" | NPC killed : "
                  << player.getPnjKilled()<<" ";

        std::string winner_or_loser = player.getIsWinner() ? "| WINNER" : "| LOSER";
        std::cout << winner_or_loser << std::endl;
    }

    int dummy;
    std::cin.clear();
    std::cin.ignore();
    std::cout << "\nEnter something and press Enter to come back in the main menu..." << std::endl;
    std::cin>>dummy;

}

Map *GameUI::getMap() const {
    return map;
}

void GameUI::display_dead_message() {
    std::cout << "You are dead. You can now watch the game peacefully" << std::endl;
}

void GameUI::displayPlayersPlacingTowersMessage() {
    std::cout << "Please wait. The remaining players are placing towers" << std::endl;
}

/* TODO: En mode par équipe, les équipes sont: NORTH & EAST, SOUTH & WEST. Adapter l'UI en mode par équipe pour
 * afficher cette information (et peut etre afficher la map du coequipier de facon differente) */
