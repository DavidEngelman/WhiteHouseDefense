
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
    while (std::cin.fail() or 0 > x or x > 7) {
        displayMenuChoices();;
        std::cout << "   Error, enter a integer between 1 and 7 " << std::endl;
        std::cout << "   Enter your choice: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> x;
    }
    menuChoice = x;
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
    std::cout << "   |        6. Settings                 |   " << std::endl;
    std::cout << "   |        7. Exit                     |   " << std::endl;
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
    std::cout << "   |        2. Timed mode               |   " << std::endl;
    std::cout << "   |        3. Team mode                |   " << std::endl;
    std::cout << "   |        4. Cancel                   |   " << std::endl;
    std::cout << "   |                                    |   " << std::endl;
    std::cout << "   ======================================   " << std::endl;
}

void MainConsoleUI::showInQueue() {
    int dummy;
    std::cout << "In queue..." << std::endl;
    std::cout << "Press any letter and enter to leave the queue" << std::endl;
    std::cin.clear();
    std::cin.ignore();
    std::cin>>dummy;
    manager->leaveQueue();
    manager->run();

}





