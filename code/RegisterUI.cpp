//
// Created by david on 12/02/17.
//

#include "RegisterUI.hpp"

RegisterUI::RegisterUI() {
    std::cout << "REGISTER SCREEN\n" << std::endl;
}

void RegisterUI::ask_username() {
    std::cout << "Enter a username:" << std::endl;
    std::cin >> username_entry;
}

void RegisterUI::ask_password() {
    std::cout << "Enter a password:" << std::endl;
    std::cin >> password_entry;
}


void RegisterUI::displayError() {
    std::cout << "Error : This username is already used or is not valid \n";
}

void RegisterUI::display() {
    ask_username();
    ask_password();
}