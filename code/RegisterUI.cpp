//
// Created by david on 12/02/17.
//

#include "RegisterUI.hpp"

RegisterUI::RegisterUI() {

    ask_username();
    ask_password();
}

std::string RegisterUI::ask_username() {

    std::string username;
    std::cout << "Enter a username:" << std::endl;
    std::cin >> username;

    return username;
}

std::string RegisterUI::ask_password() {

    std::string password;
    std::cout << "Enter a password:" << std::endl;
    std::cin >> password;

    return password;
}


void RegisterUI::displayError() {

    std::cout << "Error : username or password incorrect, please try again\n";
}

