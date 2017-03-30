
#include "MainConsoleUI.hpp"
#include "../Other/Drawing.hpp"

MainConsoleUI::MainConsoleUI(MainManager *manager) : MainUI(manager) {}

void MainConsoleUI::display() {
    displayMenuChoices();

    /* Ask at the user his choice */
    int x = -1;
    std::cin.clear();
    std::cout << "   Enter your choice: ";
    std::cin >> x;
    while (std::cin.fail() or 0 > x or x > 6) {
        displayMenuChoices();
        std::cout << "   Error, enter a integer between 1 and 6 " << std::endl;
        std::cout << "   Enter your choice: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> x;
    }
    menuChoice = x;
    // We don't have a settings menu, so the 6th option actually coresponds to the 7th option of the manager
    if (menuChoice == 6){
        menuChoice = 7;
    }
    manager->handleUserMenuChoice();
}

void MainConsoleUI::displayMenuChoices() const {
    Drawing::drawWhiteHouse("MENU SELECTION");

    std::cout << "   |                                    |   " << std::endl;
    std::cout << "   |        1. New Game                 |   " << std::endl;
    std::cout << "   |        2. Spectator                |   " << std::endl;
    std::cout << "   |        3. Profile                  |   " << std::endl;
    std::cout << "   |        4. Friend List              |   " << std::endl;
    std::cout << "   |        5. Leaderboard              |   " << std::endl;
    std::cout << "   |        6. Exit                     |   " << std::endl;
    std::cout << "   |                                    |   " << std::endl;
    std::cout << "   ======================================   " << std::endl;
}

void MainConsoleUI::displayGameModesMenu() {
    displayGameModeChoices();

    int x = -1;
    std::cout << "   Select the game mode: ";
    std::cin >> x;
    while (std::cin.fail() or x < 0 or x > 4) {
        displayGameModeChoices();
        std::cout << "   Error, enter a integer between 1 and 4 " << std::endl;
        std::cout << "   Enter your choice: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> x;
    }
    gameModeChoice = x - 1;
    manager->handleGameModeChoice();
}

void MainConsoleUI::displayGameModeChoices() const {
    Drawing::drawWhiteHouse("GAME MODE SELECTION");

    std::cout << "   |                                    |   " << std::endl;
    std::cout << "   |        1. Classic mode             |   " << std::endl;
    std::cout << "   |        2. Team mode                |   " << std::endl;
    std::cout << "   |        3. Timed mode              1 |   " << std::endl;
    std::cout << "   |        4. Cancel                   |   " << std::endl;
    std::cout << "   |                                    |   " << std::endl;
    std::cout << "   ======================================   " << std::endl;
}

void MainConsoleUI::showInQueue() {
    std::cout << "\nPress Enter to come back in the main menu..." << std::endl;
    std::cin.ignore().get();

    manager->leaveQueue();
    manager->run();

}





