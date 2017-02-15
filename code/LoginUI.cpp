
#include "LoginUI.hpp"
#include "Drawing.hpp"
#include "unistd.h"

LoginUI::LoginUI() {
    Drawing::drawWhiteHouse("LOGIN SCREEN");
}

void LoginUI::ask_username() {
    std::cout << "   Enter your username:" << std::endl << "   ";
    std::cin >> username_entry;
    std::cin.clear();
    std::cin.ignore();
}

void LoginUI::ask_password() {
    std::cout << "   Enter your password:" << std::endl << "   ";
    std::cin >> password_entry;
    std::cin.clear();
    std::cin.ignore();

    //password_entry = crypt(password_entry.c_str(), "g4");

}

void LoginUI::displayError() {
    std::cout << "   Error : username or password incorrect, please try again\n";
}

void LoginUI::display() {
    ask_username();
    ask_password();
}

