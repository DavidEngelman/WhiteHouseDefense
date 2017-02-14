
#include "MainUI.hpp"

void MainUI::display() {
    /*Show user's menu*/

    std::cout << "                _ _.-''-._ _                " << std::endl;
    std::cout << "               ;.'________'.;               " << std::endl;
    std::cout << "    _________n.[____________].n_________    " << std::endl;
    std::cout << "   |\"\"_\"\"_\"\"_\"\"||==||==||==||\"\"_\"\"_\"\"_\"\"]   " << std::endl;
    std::cout << "   |\"\"\"\"\"\"\"\"\"\"\"||..||..||..||\"\"\"\"\"\"\"\"\"\"\"|   " << std::endl;
    std::cout << "   |LI LI LI LI||LI||LI||LI||LI LI LI LI|   " << std::endl;
    std::cout << "   |.. .. .. ..||..||..||..||.. .. .. ..|   " << std::endl;
    std::cout << "   |LI LI LI LI||LI||LI||LI||LI LI LI LI|   " << std::endl;
    std::cout << "   ======================================   " << std::endl;
    std::cout << "   |        White House Defense         |   " << std::endl;
    std::cout << "   ======================================   " << std::endl;
    std::cout << "   |           MENU SELECTION           |   " << std::endl;
    std::cout << "   ======================================   " << std::endl;
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
    std::cout << "Enter your choice --> ";
    std::cin >> x;
    while(std::cin.fail() or 0>x or x>6){
        display();
        std::cout << "Error, enter a integer between 1 and 5 " << std::endl;
        std::cout << "Enter your choice --> ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> x;
    }
    return x;
}

void MainUI::exit() {
    //TODO
}