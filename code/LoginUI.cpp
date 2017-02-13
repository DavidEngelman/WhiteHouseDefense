
#include "LoginUI.hpp"

LoginUI::LoginUI() {
    std::cout << "LOGIN SCREEN\n" << std::endl;
}

void LoginUI::ask_username() {
    std::cout << "Enter a username:" << std::endl;
    std::cin >> username_entry;
}

void LoginUI::ask_password() {
    std::cout << "Enter a password:" << std::endl;
    std::cin >> password_entry;
}


void LoginUI::displayError() {
    std::cout << "Error : username or password incorrect, please try again\n";
}

void LoginUI::display() {
    ask_username();
    ask_password();
}

