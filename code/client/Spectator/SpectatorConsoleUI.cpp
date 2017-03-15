
#include <iostream>
#include "SpectatorConsoleUI.hpp"

SpectatorConsoleUI::SpectatorConsoleUI(SpectatorManager *spectatorManager) : SpectatorUI(spectatorManager) {}

void SpectatorConsoleUI::display() {
    system("clear");
    std::cout << "Here are the games being played at the moment: " << std::endl;
    int i = 1;
    for( GameInfo game : allGames) {
        std::cout << "Game " << i << ": ";
        game.print();
        i++;
    }
}

void SpectatorConsoleUI::displaySorryMessage() {
    int i;
    system("clear");
    std::cout << "Sorry, no games in progress... :(" << std::endl;
    std::cout << "Enter something to come back to menu..." << std::endl;
    std::cin >> i;
    std::cin.clear();
    std::cin.ignore();

    spectatorManager->goToMainMenu();
}

void SpectatorConsoleUI::gameSelection(int number_of_games_available) {
    int choice = -1;
    std::cout << "Enter the number of the game you want to spectate: ";
    std::cin >> choice;
    while(std::cin.fail() || (choice < 1 || choice > number_of_games_available) ){
        std::cout << "Error, enter a integer between 1 and "<< number_of_games_available << std::endl;
        std::cout <<"Enter the number of the game you want to spectate: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> choice;
    }
    spectatorManager->setGameSelected(choice -1);
}

void SpectatorConsoleUI::playerSelection(GameInfo& game_info) {
    std::string choice = "";
    std::cout << "Enter the username of the player you want to support: ";
    std::cin >> choice;
    while(std::cin.fail() || !(game_info.isInPlayers(choice))) {
        std::cout << "Error, username incorrect " << std::endl;
        std::cout << "Enter the username of the player you want to support: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> choice;
    }
    spectatorManager->setPlayerSelected(choice);
}

void SpectatorConsoleUI::selectGameAndPlayer() {
    display();
    gameSelection((int) allGames.size());
    playerSelection(allGames[spectatorManager->getGameSelected()]);
    int gamePort = allGames[spectatorManager->getGameSelected()].getPort();
    spectatorManager->connectToGame(gamePort, spectatorManager->getPlayerSelected());
}
