

#include <termios.h>
#include "LoginConsoleUI.hpp"
#include "../Other/Drawing.hpp"

void LoginConsoleUI::ask_username() {
    std::cout << "   Enter your username:" << std::endl << "   ";
    std::cin >> username;
    std::cin.clear();
    std::cin.ignore();
}

void LoginConsoleUI::ask_password() {
    std::cout << "   Enter your password:" << std::endl << "   ";

    // Disable the echo when entering the password
    termios oldt;
    tcgetattr(STDIN_FILENO, &oldt);
    termios newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    std::cin >> password;

    // Enable the echo
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    std::cin.clear();
    std::cin.ignore();
}

void LoginConsoleUI::displayError() {
    Drawing::drawWhiteHouse("LOGIN SCREEN");
    std::cout << "   Error : username or password incorrect, please try again\n";
    ask_username();
    ask_password();
    manager->login();
}

void LoginConsoleUI::display() {
    Drawing::drawWhiteHouse("LOGIN SCREEN");
    ask_username();
    ask_password();
    manager->login();
}

void LoginConsoleUI::displayAlreadyConnected() {
    Drawing::drawWhiteHouse("LOGIN SCREEN");
    std::cout << "   Error : Someone is already connected on this account :(\n";
    ask_username();
    ask_password();
    manager->login();
}

std::string LoginConsoleUI::getUsername() {
    return username;
}

std::string LoginConsoleUI::getPassword() {
    return password;
}

LoginConsoleUI::LoginConsoleUI(LoginManager *manager) : LoginUI(manager) {

}

