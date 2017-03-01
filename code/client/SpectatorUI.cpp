//
//

#include <iostream>
#include "SpectatorUI.hpp"
#include "Drawing.hpp"

void SpectatorUI::displaySpectatorUI(std::vector<GameInfo>& gamesInfos) {

    std::cout << "Here are the games being played at the moment: \n" << std::endl;
    int i = 0;
    for( GameInfo game : gamesInfos) {
        std::cout << "Game " << i << " - Mode: " << game.gameMode << " - Players: " << game.players << std::endl;
        i++;
    }

    if (i == 0){
        std::cout << "Sorry, no games in progress... :(" << std::endl;
    }


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
