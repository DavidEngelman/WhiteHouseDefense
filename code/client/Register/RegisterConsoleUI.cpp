#include <termios.h>
#include "RegisterConsoleUI.hpp"
#include "../Other/Drawing.hpp"

RegisterConsoleUI::RegisterConsoleUI(RegisterManager *manager) : RegisterUI(manager) {}

void RegisterConsoleUI::ask_username() {
    std::cout << "   Enter a username:     ( 16 characters max. )" << std::endl << "   ";
    std::cin >> username;

    std::cin.clear();
    std::cin.ignore();
}

void RegisterConsoleUI::ask_password() {
    // Disable the echo when entering the password
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::cout << "   Enter a password:" << std::endl << "   ";
    std::cin >> password;
    std::cout << std::endl;

    std::cin.clear();
    std::cin.ignore();

    std::cout << "   Confirm your password:" << std::endl << "   ";
    std::cin >> confirm;

    // Enable the echo
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
}


void RegisterConsoleUI::displayError() {
    Drawing::drawWhiteHouse("REGISTER SCREEN");
    std::cout << "   Error : This username is already used or is not valid" << std::endl;
    ask_username();
    ask_password();
    manager->registerUser();
}

void RegisterConsoleUI::displaySuccess() {
    Drawing::drawWhiteHouse("REGISTER SCREEN");
    std::cout <<"    Success : Your account has been successfully registered" << std::endl;

    std::cout << "\nPress Enter to go to the login screen..." << std::endl;
    std::cin.ignore().get();
}

void RegisterConsoleUI::displayConfirmError() {
    Drawing::drawWhiteHouse("REGISTER SCREEN");
    std::cout << "   Error : Your password doesn't correspond to the confirmation" << std::endl;
    ask_username();
    ask_password();
    manager->registerUser();
}

void RegisterConsoleUI::display() {
    Drawing::drawWhiteHouse("REGISTER SCREEN");
    ask_username();
    ask_password();
    manager->registerUser();
}