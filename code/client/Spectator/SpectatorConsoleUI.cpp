
#include <iostream>
#include "SpectatorConsoleUI.hpp"

SpectatorConsoleUI::SpectatorConsoleUI(SpectatorManager *spectatorManager) : SpectatorUI(spectatorManager) {}

void SpectatorConsoleUI::getGameAndPlayer() {
    int choice = -1;
    displayCurrentGames();
    std::cout << "Enter the number of the game you want to spectate: ";
    std::cin >> choice;
    while (std::cin.fail() || (choice < 1 || choice > (*_games).size())) {
        displayCurrentGames();
        std::cout << "Error, enter a integer between 1 and " << (*_games).size() << std::endl;
        std::cout << "Enter the number of the game you want to spectate: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> choice;
    }
    selectPlayerForGame(choice - 1);
}

void SpectatorConsoleUI::displayCurrentGames() {
    system("clear");
    std::cout << "Here are the games being played at the moment: " << std::endl;
    int gameIndex = 1;
    for (GameInfo game : *_games) {
        std::cout << "Game " << gameIndex << ": ";
        game.print();
        gameIndex++;
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
}



void SpectatorConsoleUI::selectPlayerForGame(int gameIndex) {
    selectedGame = &((*_games)[gameIndex]);
    std::string playerName = askUserToSelectPlayer();
    handlePlayerSelection(playerName);
}

std::string SpectatorConsoleUI::askUserToSelectPlayer() {
    std::string playerNameUserInput = "";
    showPlayersForCurrentGame();
    std::cout << "Enter the username of the player you want to support: ";
    std::cin >> playerNameUserInput;
    while (std::cin.fail() || !(selectedGame->isInPlayers(playerNameUserInput))) {
        showPlayersForCurrentGame();
        std::cout << "Error, username incorrect " << std::endl;
        std::cout << "Enter the username of the player you want to support: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> playerNameUserInput;
    }
    return playerNameUserInput;
}

void SpectatorConsoleUI::showPlayersForCurrentGame(){
    std::cout << std::endl << "Here are the games being played at the moment: " << std::endl;
    int playerIndex = 1;
    for (std::string playerName : selectedGame->getPlayers()) {
        std::cout << "Player " << playerIndex << ": " << playerName << std::endl;
        playerIndex++;
    }
}

