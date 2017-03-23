#include "WelcomeConsoleUI.hpp"
#include "../Other/Drawing.hpp"

WelcomeConsoleUI::WelcomeConsoleUI(WelcomeManager *manager) : WelcomeUI(manager) {}

void WelcomeConsoleUI::display() {
    /*Show user's menu*/
    Drawing::drawWhiteHouse("LAUNCHER");
    std::cout << "   |       1. Log In                    |   " << std::endl;
    std::cout << "   |       2. Register                  |   " << std::endl;
    std::cout << "   |       3. Exit                      |   " << std::endl;
    std::cout << "   ======================================   " << std::endl;
}

int WelcomeConsoleUI::select() {
    /* Ask for user's choice */
    int choice = -1;
    std::cout << "Enter your choice:  ";
    std::cin >> choice;
    while (std::cin.fail() or 0 > choice or choice > 3) {
        display();
        std::cout << "   Error, enter a integer between 1 and 3" << std::endl;
        std::cout << "   Enter your choice: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> choice;
    }
    return choice;
}