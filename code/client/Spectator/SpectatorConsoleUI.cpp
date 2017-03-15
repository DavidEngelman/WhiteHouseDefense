
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

void SpectatorConsoleUI::gameSelection_input() {
    int choice = -1;
    std::cout << "Enter the number of the game you want to spectate: ";
    std::cin >> choice;
    while(std::cin.fail() || (choice < 1 || choice > allGames.size()) ){
        std::cout << "Error, enter a integer between 1 and "<< allGames.size() << std::endl;
        std::cout <<"Enter the number of the game you want to spectate: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> choice;
    }
    gameSelection(choice - 1);
}

void SpectatorConsoleUI::gameSelection(int game_index){
    spectatorManager->setGameSelected(game_index);
}

void SpectatorConsoleUI::playerSelection_input(GameInfo& game_info) {
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
    playerSelection(choice);
}

void SpectatorConsoleUI::playerSelection(std::string player_name) {
    spectatorManager->setPlayerSelected(player_name);
}

void SpectatorConsoleUI::selectGameAndPlayerProcess() {

    if (allGames.size() == 0){
        displaySorryMessage();
    } else{
        display();
        gameSelection_input();
        playerSelection_input(allGames[spectatorManager->getGameSelected()]);
        int gamePort = allGames[spectatorManager->getGameSelected()].getPort();
        spectatorManager->connectToGame(gamePort, spectatorManager->getPlayerSelected());
    }


}


