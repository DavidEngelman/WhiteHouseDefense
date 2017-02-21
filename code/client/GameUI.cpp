//
// Created by jepsiko on 21/02/17.
//

#include "GameUI.hpp"
#include <iostream>

GameUI::GameUI(){
    Map map = Map ();//rajouter seed
}

void GameUI::getUserCommands() {
    int x;
    int y;
    std::cout << "Entrez les coordonnées de l'endroit où vous voulez placer une tour" << std::endl;
    std::cout << "Entrez un X:";
    std::cin >> x;
    std::cout << "Entrez un Y:";
    std::cin >> y;
}

void GameUI::draw(GameState gameState) {

}

void GameUI::showNoInternetError() {

}

void GameUI::display() {
    map.display();
}
