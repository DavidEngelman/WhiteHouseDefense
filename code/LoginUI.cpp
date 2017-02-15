
#include "LoginUI.hpp"
#include "Drawing.hpp"

LoginUI::LoginUI() {
    Drawing::drawWhiteHouse("LOGIN SCREEN");
}

void LoginUI::ask_username() {
    std::cout << "   Enter your username:" << std::endl << "   ";
    std::cin >> username_entry;
    std::cin.ignore(100,'\n');
}

void LoginUI::ask_password() {
    std::cout << "   Enter your password:" << std::endl << "   ";
    std::cin >> password_entry;
    std::cin.ignore(100,'\n');
}

void LoginUI::displayError() {
    std::cout << "   Error : username or password incorrect, please try again\n";
}

void LoginUI::display() {
    ask_username();
    ask_password();
}

