

#include <termios.h>
#include "RegisterUI.hpp"
#include "../Drawing.hpp"
#include "unistd.h"

RegisterUI::RegisterUI() {}

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
}


void RegisterUI::displayError() {
    Drawing::drawWhiteHouse("REGISTER SCREEN");
    std::cout << "   Error : This username is already used or is not valid \n";
}

void RegisterUI::displayConfirmError() {
    Drawing::drawWhiteHouse("REGISTER SCREEN");
    std::cout << "   ERROR : Your password doesn't correspond to the confirmation" << std::endl;
}

void RegisterUI::display() {
    Drawing::drawWhiteHouse("REGISTER SCREEN");
    ask_username();
    ask_password();
}