#include "Drawing.hpp"
#include <iostream>

void Drawing::drawWhiteHouse(std::string title) {
    unsigned long nbSpace = 36 - title.length();
    std::cout << "                _ _.-''-._ _                " << std::endl;
    std::cout << "               ;.'________'.;               " << std::endl;
    std::cout << "    _________n.[____________].n_________    " << std::endl;
    std::cout << "   |\"\"_\"\"_\"\"_\"\"||==||==||==||\"\"_\"\"_\"\"_\"\"]   " << std::endl;
    std::cout << "   |\"\"\"\"\"\"\"\"\"\"\"||..||..||..||\"\"\"\"\"\"\"\"\"\"\"|   " << std::endl;
    std::cout << "   |LI LI LI LI||LI||LI||LI||LI LI LI LI|   " << std::endl;
    std::cout << "   |.. .. .. ..||..||..||..||.. .. .. ..|   " << std::endl;
    std::cout << "   |LI LI LI LI||LI||LI||LI||LI LI LI LI|   " << std::endl;
    std::cout << "   ======================================   " << std::endl;
    std::cout << "   |        WHITE HOUSE DEFENSE         |   " << std::endl;
    std::cout << "   ======================================   " << std::endl;
    std::cout << "   |" << std::string(nbSpace/2, ' ') << title << std::string(nbSpace/2, ' ');
    if (title.length() % 2 == 1) std::cout << " ";
    std::cout << "|" << std::endl;
    std::cout << "   ======================================   " << std::endl;
}