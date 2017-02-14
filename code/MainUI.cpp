
#include "MainUI.hpp"

void MainUI::display() {
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
    int x = -1;
    std::cout << "Enter your choice --> ";
    std::cin >> x;
    while(std::cin.fail() or 0>x or x>6){
        std::cout << "Error" << std::endl;
        std::cin.clear();
        std::cin.ignore(256,'\n');
        std::cout << "Enter your choice --> ";
        std::cin >> x;
    }

    std::cout << "ok" << std::endl;
    std::cout << "x:"<< x << std::endl;


}