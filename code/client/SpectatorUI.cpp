//
//

#include <iostream>
#include "SpectatorUI.hpp"
#include "Drawing.hpp"

void SpectatorUI::displaySpectatorUI() {
    int i=0;
    Drawing::drawWhiteHouse("SPECTATOR SCREEN");
    //for type de partie;
        //drawTitleGameType(gameType);
    //std::cout<<type de partie<<std//endl;
    //for()//pour chaque partie
    //std::cout<<i<<") "<<partie<<"("<<nom_joueur<<")"<<std::endl;

}

int SpectatorUI::inputSpectatorUI() {
    int choice;
    std::cout<<"Enter the number of the game that you would like to see: ";
    std::cin >> choice;

    return choice;
}

void SpectatorUI::drawTitleGameType(std::string gameType) {
    unsigned long nbSpace = (36 - gameType.length()) / 2;
    std::cout << "   ======================================   " << std::endl;
    std::cout << "   |" << std::string(nbSpace, ' ') << gameType << std::string(nbSpace, ' ');
    if (gameType.length() % 2 == 1) std::cout << " ";
    std::cout << "|" << std::endl;
    std::cout << "   ======================================   " << std::endl;

}
