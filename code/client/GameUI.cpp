//
// Created by jepsiko on 21/02/17.
//

#include "GameUI.hpp"
#include <iostream>

GameUI::GameUI(){
    map = Map (); //rajouter seed
}

std::string GameUI::getCoordTower() {
    int x;
    int y;

    do {
        std::cout << "Entrez les coordonnées de l'endroit où vous voulez placer une tour" << std::endl;
        std::cout << "Entrez un X: ";
        std::cin >> x;
        std::cout << "Entrez un Y: ";
        std::cin >> y;
    } while (!checkCoord(x,y));

    return concatCoord(x, y);
}

bool GameUI::checkCoord(int x, int y){
    if (0 <= x and x < SIZE and 0 <= y and y < SIZE){
        return true;
    }
    display();
    std::cout<< "Entrez un x et un y entre 0 et "<<SIZE-1<< std::endl;
    return false;

}

void GameUI::display() {
    map.display();
}

std::string GameUI::concatCoord(int x,int y){
    std::string coord = "";
    if (x < 10){
        coord = "0";
    }
    coord += std::to_string(x) + " ";
    if (y < 10){
        coord = "0";
    }

    return coord + std::to_string(y);
}
