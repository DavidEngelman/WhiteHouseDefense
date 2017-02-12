//
// Created by david on 12/02/17.
//

#include "RegisterUI.hpp"


void RegisterUI::ask_username() {
    std::cout << "Enter a username:" << std::endl;
    std::cin >> username_entry;
}

void RegisterUI::ask_password() {
    std::cout << "Enter a password:" << std::endl;
    std::cin >> password_entry;
}


void RegisterUI::displayError() {
    std::cout << "Error : username or password incorrect, please try again\n";
}

void RegisterUI::display() {
    ask_username();
    ask_password();
}