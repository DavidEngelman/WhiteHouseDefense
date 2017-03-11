#include "ProfileConsoleUI.hpp"


ProfileConsoleUI::ProfileConsoleUI(ProfileManager *profileManager) : ProfileUI(profileManager) {}

void ProfileConsoleUI::displayMenu() {
    /*Show user's menu*/
    std::cout << "   ======================================   " << std::endl;
    std::cout << "   |       1. My Profile                |   " << std::endl;
    std::cout << "   |       2. Search profile            |   " << std::endl;
    std::cout << "   |       3. Return to Main Menu       |   " << std::endl;
    std::cout << "   ======================================   " << std::endl;
}

void ProfileConsoleUI::display() {
    /* Ask at the user his choice */
    int userChoice = -1;
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

void ProfileConsoleUI::displayProfile(std::string profileData) {
    // TODO: simplify this code enormously by using a Command (bad class name; refactoring probably needed)
    int counter = 0;
    std::string username = "";
    while (profileData[counter] != ',') {
        username += profileData[counter];
        counter++;
    }
    std::cout << "Username : " << username << std::endl;
    counter++;
    std::string victories = "";
    while (profileData[counter] != ',') {
        victories += profileData[counter];
        counter++;
    }
    std::cout << "Victories : " << victories << std::endl;
    counter++;
    std::string pnjKilled = "";
    while (profileData[counter] != ';') {
        pnjKilled += profileData[counter];
        counter++;
    }
    std::cout << "Pnj Killed : " << pnjKilled << std::endl;

}

void ProfileConsoleUI::displayNoSuchProfileError() {
    std::cout << "No profile was found with that username" << std::endl;
}
