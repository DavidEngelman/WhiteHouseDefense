
#include "LoginUI.hpp"

LoginUI::LoginUI() {
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
    std::cout << "   |            LOGIN SCREEN            |   " << std::endl;
    std::cout << "   ======================================   " << std::endl;
}

void LoginUI::ask_username() {
    std::cout << "   Enter your username:" << std::endl;
    std::cin >> username_entry;
}

void LoginUI::ask_password() {
    std::cout << "   Enter your password:" << std::endl;
    std::cin >> password_entry;
}

void LoginUI::displayError() {
    std::cout << "   Error : username or password incorrect, please try again\n";
}

void LoginUI::display() {
    ask_username();
    ask_password();
}

