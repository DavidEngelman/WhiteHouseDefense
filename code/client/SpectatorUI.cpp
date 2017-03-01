//
//

#include <iostream>
#include "SpectatorUI.hpp"
#include "Drawing.hpp"

void SpectatorUI::displaySpectatorUI(std::vector<GameInfo>& gamesInfos) {
    system("clear");
    std::cout << "Here are the games being played at the moment: " << std::endl;
    int i = 1;
    for( GameInfo game : gamesInfos) {
        std::cout << "Game " << i << " - Mode: " << game.gameMode << " - Players: " << game.players << std::endl;
        i++;
    }
}

void SpectatorUI::displaySorryMessage() {
    int i;
    std::cout << "Sorry, no games in progress... :(" << std::endl;
    std::cout << "Enter something to come back to menu..." << std::endl;
    std::cin >> i;
}

int SpectatorUI::inputSpectatorUI(int number_of_games_available) {
    int choice = -1;
    std::cout << "Enter the number of the game you want to spectate: " << std::endl;
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
