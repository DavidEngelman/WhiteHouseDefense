#include "ProfileConsoleUI.hpp"


ProfileConsoleUI::ProfileConsoleUI(ProfileManager *profileManager) : ProfileUI(profileManager) {}

void ProfileConsoleUI::displayMenu() {
    std::cout << "   ======================================   " << std::endl;
    std::cout << "   |       1. My Profile                |   " << std::endl;
    std::cout << "   |       2. Search profile            |   " << std::endl;
    std::cout << "   |       3. Return to Main Menu       |   " << std::endl;
    std::cout << "   ======================================   " << std::endl;
}

void ProfileConsoleUI::display() {
    /* Ask at the user his choice */
    int userChoice = -1;
    displayMenu();
    std::cout << "   Enter your choice: ";
    std::cin >> userChoice;
    while (std::cin.fail() or userChoice < 0 or userChoice > 3) {
        displayMenu();
        std::cout << "   Error, enter a integer between 1 and 3" << std::endl;
        std::cout << "   Enter your choice: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> userChoice;
    }

    choice = userChoice;
    /* Call the appropriate manager method */
    if (choice == 1) {
        profileManager->showMyProfile();
    } else if (choice == 2){
        askUsername();
        profileManager->showProfile();
    } else if (choice == 3) {
        profileManager->goToMainMenu();
    }
}

void ProfileConsoleUI::askUsername() {
    std::cout << "Profile's username : ";
    std::string userName;
    std::cin >> userName;
    std::cout << std::endl;

    username = userName;
}

void ProfileConsoleUI::updateProfile() {
    std::cout << "Username : " << profileManager->getUsername() << std::endl;
    std::cout << "Victories : " << profileManager->getVictories() << std::endl;
    std::cout << "NPC Killed : " << profileManager->getNPCKilled() << std::endl;
    display();
}

void ProfileConsoleUI::displayNoSuchProfileError() {
    std::cout << "No profile was found with that username" << std::endl;
    display();
}
