
#include "MainUI.hpp"
#include "Drawing.hpp"

void MainUI::display() {
    /*Show user's menu*/
    Drawing::drawWhiteHouse("MENU SELECTION");

    std::cout << "   |                                    |   " << std::endl;
    std::cout << "   |        1. New Game                 |   " << std::endl;
    std::cout << "   |        2. Profile                  |   " << std::endl;
    std::cout << "   |        3. Friend List              |   " << std::endl;
    std::cout << "   |        4. Leaderboard              |   " << std::endl;
    std::cout << "   |        5. Exit                     |   " << std::endl;
    std::cout << "   |                                    |   " << std::endl;
    std::cout << "   ======================================   " << std::endl;

}

int MainUI::select(){
    /* Ask at the user his choice */
    int x = -1;
    std::cin.clear();
    std::cout << "   Enter your choice: ";
    std::cin >> x;
    while(std::cin.fail() or 0>x or x>=6){
        display();
        std::cout << "   Error, enter a integer between 1 and 5 " << std::endl;
        std::cout << "   Enter your choice: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> x;
    }
    return x;
}

void MainUI::displayGameModes() {
    Drawing::drawWhiteHouse("GAME MODE SELECTION");

    std::cout << "   |                                    |   " << std::endl;
    std::cout << "   |        1. Classic mode             |   " << std::endl;
    std::cout << "   |        2. Timed mode               |   " << std::endl;
    std::cout << "   |        3. Team mode                |   " << std::endl;
    std::cout << "   |                                    |   " << std::endl;
    std::cout << "   ======================================   " << std::endl;

}

int MainUI::selectGameMode() {
    int x = -1;
    std::cout << "   Select the game mode: ";
    std::cin >> x;
    while(std::cin.fail() or 0>x or x>=4){
        displayGameModes();
        std::cout << "   Error, enter a integer between 1 and 4 " << std::endl;
        std::cout << "   Enter your choice: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> x;
    }
    return x;

}

