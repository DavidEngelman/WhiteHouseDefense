

#include <termios.h>
#include "RegisterUI.hpp"
#include "../Drawing.hpp"
#include "unistd.h"

RegisterUI::RegisterUI() {
    Drawing::drawWhiteHouse("REGISTER SCREEN");
}

void RegisterUI::ask_username() {
    std::cout << "   Enter a username:     ( 16 characters max. )" << std::endl << "   ";
    std::cin >> username_entry;
    std::cin.clear();
    std::cin.ignore();
}

void RegisterUI::ask_password() {
    std::string confirm;

    // Disable the echo when entering the password
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::cout << "   Enter a password:" << std::endl << "   ";
    std::cin >> password_entry;
    std::cout << std::endl;

    std::cin.clear();
    std::cin.ignore();

    std::cout << "   Confirm your password:" << std::endl << "   ";
    std::cin >> confirm;

    std::cin.clear();
    std::cin.ignore();

    // Enable the echo
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    if (confirm != password_entry) {
        Drawing::drawWhiteHouse("REGISTER SCREEN");
        std::cout << "   ERROR : Your password doesn't correspond to the confirmation" << std::endl;
        display();
    } else {
        password_entry = crypt(password_entry.c_str(), "g4");
        for (unsigned i = 0; i < password_entry.length(); i++) {
            if (password_entry[i] == ',' || password_entry[i] == ';') password_entry.erase(i);
        }
    }
}


void RegisterUI::displayError() {
    Drawing::drawWhiteHouse("REGISTER SCREEN");
    std::cout << "   Error : This username is already used or is not valid \n";
}

void RegisterUI::display() {
    ask_username();
    ask_password();
}