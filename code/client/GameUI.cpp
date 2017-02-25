#include "GameUI.hpp"
#include <iostream>


GameUI::GameUI(Map &map) : map(map) {
}

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
    display();
    std::cout << "Entrez un x et un y entre 0 et " << SIZE - 1 << std::endl;
    return false;
}

void GameUI::display() {
    map.display();
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
            display();
            std::cout << "Veuillez entrer '1' ou '2'" << std::endl;
        }

    } while (!ok);

    return response == 1;
}
