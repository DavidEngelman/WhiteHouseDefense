#include "../../common/Constants.h"
#include "ProfileManager.hpp"
#include "ProfileGUI.hpp"
#include "ProfileConsoleUI.hpp"

ProfileManager::ProfileManager(int port, App *my_app) :
        NetworkedManager(port, my_app) {
    if (isConsole) {
        profileUI = new ProfileConsoleUI(this);
    } else {
        profileUI = new ProfileGUI(this);
    }
}

void ProfileManager::run() {
    profileUI->display();
}

void ProfileManager::showMyProfile() {
    profileUI->displayProfile(getProfile(master_app->get_username()));
}

void ProfileManager::showProfile() {
    std::string profile = profileUI->getUsername();
    std::string server_response = getProfile(profile);
    if (server_response.size() == 3) { // le serveur renvoie ,,;
        profileUI->displayNoSuchProfileError();
    } else {
        profileUI->displayProfile(server_response);
    }
}

void ProfileManager::goToMainMenu() {
    MainManager *mainManager = new MainManager(ACCOUNT_SERVER_PORT, master_app);
    master_app->transition(mainManager);
}

std::string ProfileManager::getProfile(std::string username) {
    std::string message = GET_PROFILE + username + ";";
    send_message(server_socket, message.c_str());
    char buffer[MAX_BUFF_SIZE];
    receive_message(server_socket, buffer);
    return std::string(buffer);
}

std::string ProfileManager::getUsername() {
    std::cout << master_app->get_username() << std::endl;
    return master_app->get_username();
}


