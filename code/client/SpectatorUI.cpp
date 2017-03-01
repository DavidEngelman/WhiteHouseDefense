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
        std::cout << "Game " << i << ": ";
        game.print();
        i++;
    }
}

void SpectatorUI::displaySorryMessage() {
    int i;
    system("clear");
    std::cout << "Sorry, no games in progress... :(" << std::endl;
    std::cout << "Enter something to come back to menu..." << std::endl;
    std::cin >> i;
    std::cin.clear();
    std::cin.ignore();
}

int SpectatorUI::inputSpectatorUI(int number_of_games_available) {
    int choice = -1;
    std::cout << "   Enter your choice: ";
    std::cin >> choice;
    while(std::cin.fail() || (choice < 1 || choice > number_of_games_available) ){
        std::cout << "   Error, enter a integer between 1 and "<< number_of_games_available << std::endl;
        std::cout << "   Enter your choice: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> choice;
    }
    return choice -1;
}

void SpectatorUI::drawTitleGameType(std::string gameType) {
    unsigned long nbSpace = (36 - gameType.length()) / 2;
    std::cout << "   ======================================   " << std::endl;
    std::cout << "   |" << std::string(nbSpace, ' ') << gameType << std::string(nbSpace, ' ');
    if (gameType.length() % 2 == 1) std::cout << " ";
    std::cout << "|" << std::endl;
    std::cout << "   ======================================   " << std::endl;

}
