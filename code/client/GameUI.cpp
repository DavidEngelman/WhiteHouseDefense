#include "GameUI.hpp"
#include <iostream>


GameUI::GameUI(unsigned seed) : map(new Map(seed)) {}

Position GameUI::getPosBuyingTower() {
    int x;
    int y;

    do {
        std::cout << "Entrez les coordonnées de l'endroit où vous voulez placer une tour" << std::endl;
        std::cout << "Entrez un X: ";
        std::cin >> x;
        std::cout << "Entrez un Y: ";
        std::cin >> y;
    } while (!checkCoord(x, y));

    return Position(x, y);
}

bool GameUI::checkCoord(int x, int y) {
    if (0 <= x and x < SIZE and 0 <= y and y < SIZE) {
        return true;
    }
    std::cout << "Entrez un x et un y entre 0 et " << SIZE - 1 << std::endl;
    return false;
}

void GameUI::display(GameState& gameState) {
    map->display(gameState);
}

void GameUI::display(int quadrant) {
    std::cout << "Votre quadrant est le : " << quadrant << std::endl;
}

bool GameUI::isBuyingTower() {
    int response;
    bool ok = false;

    do {
        std::cout << "Voulez-vous :\n1) Acheter une tour ?\n2) Vendre une tour ?" << std::endl;
        std::cin >> response;
        if (!std::cin.fail() and (response == 1 or response == 2)) {
            ok = true;
        } else {
            std::cout << "Veuillez entrer '1' ou '2'" << std::endl;
        }

    } while (!ok);

    return response == 1;
}

Position GameUI::getPosSellingTower() {
    int x;
    int y;

    do {
        std::cout << "Entrez les coordonnées de la tour que vous voulez vendre" << std::endl;
        std::cout << "Entrez un X: ";
        std::cin >> x;
        std::cout << "Entrez un Y: ";
        std::cin >> y;
    } while (!checkCoord(x, y));

    return Position(x, y);
}

std::string GameUI::bool_to_string(bool my_bool){
    return my_bool ? "true" : "false";
}

void GameUI::displayPlayerInfos(GameState& gameState, int& quadrant) {
    int gold = gameState.getPlayerStates()[quadrant].getMoney();
    int pnj_killed = gameState.getPlayerStates()[quadrant].getPnjKilled();
    int hp = gameState.getPlayerStates()[quadrant].getHp();
    bool isSupported = gameState.getPlayerStates()[quadrant].getIsSupported();

    std::string infos = "Money: " + std::to_string(gold) + "\tNPC killed: " + std::to_string(pnj_killed)
    +"\nHP: " + std::to_string(hp) + "\tSupported: " + bool_to_string(isSupported);

    std::cout << infos << std::endl;
}
void GameUI::displayPosingPhase() {

    std::cout << "1. Buy tower " << std::endl;
    std::cout << "2. Sell tower " << std::endl;
    std::cout << "3. Upgrade tower " << std::endl;
    std::cout << std::endl;

    std::cout << "Your choice :   ";
}
void GameUI::displayTowerShop() {
    std::cout << "1. Attacktower " << std::endl;
    std::cout << std::endl;
    // put other tower types here
    std::cout << "Your choice :   ";
}

int GameUI::getChoice() {
    /* Ask at the user his choice */
    int x = -1;
    std::cout << "   Enter your choice: ";
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