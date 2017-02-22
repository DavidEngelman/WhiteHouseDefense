//
// Created by jepsiko on 21/02/17.
//

#include "GameUI.hpp"
#include <iostream>

GameUI::GameUI(){
    Map map = Map ();//rajouter seed
}

std::string GameUI::getCoordTower() {
    int x;
    int y;
    std::string res;
    std::cout << "Entrez les coordonnées de l'endroit où vous voulez placer une tour" << std::endl;
    std::cout << "Entrez un X:";
    std::cin >> x;
    std::cout << "Entrez un Y:";
    std::cin >> y;

    return concatCoord(x,y);
}



void GameUI::showNoInternetError() {

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
