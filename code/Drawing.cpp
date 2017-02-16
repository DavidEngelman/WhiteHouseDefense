#include "Drawing.hpp"
#include <iostream>

void Drawing::drawWhiteHouse(std::string title) {
    std::cout << std::string(50, '\n');
    if (title.length() > 36) return;
    unsigned long nbSpace = (36 - title.length()) / 2;
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
    std::cout << "   |" << std::string(nbSpace, ' ') << title << std::string(nbSpace, ' ');
    if (title.length() % 2 == 1) std::cout << " ";
    std::cout << "|" << std::endl;
    std::cout << "   ======================================   " << std::endl;
}