
#include "RegisterUI.hpp"
#include "Drawing.hpp"

RegisterUI::RegisterUI() {
    Drawing::drawWhiteHouse("REGISTER SCREEN");
}

void RegisterUI::ask_username() {
    std::cout << "   Enter a username:     ( 16 characters max. )" << std::endl << "   ";
    std::cin >> username_entry;
    std::cin.ignore(100,'\n');
}

void RegisterUI::ask_password() {
    std::cout << "   Enter a password:" << std::endl << "   ";
    std::cin >> password_entry;
    std::cin.ignore(100,'\n');
}


void RegisterUI::displayError() {
    std::cout << "   Error : This username is already used or is not valid \n";
}

void RegisterUI::display() {
    ask_username();
    ask_password();
}