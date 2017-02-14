//
// Created by david on 12/02/17.
//

#include "RegisterUI.hpp"

RegisterUI::RegisterUI() {
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
    std::cout << "   |          REGISTER SCREEN           |   " << std::endl;
    std::cout << "   ======================================   " << std::endl;
}

void RegisterUI::ask_username() {
    std::cout << "   Enter a username:" << std::endl;
    std::cin >> username_entry;
}

void RegisterUI::ask_password() {
    std::cout << "   Enter a password:" << std::endl;
    std::cin >> password_entry;
}


void RegisterUI::displayError() {
    std::cout << "   Error : This username is already used or is not valid \n";
}

void RegisterUI::display() {
    ask_username();
    ask_password();
}