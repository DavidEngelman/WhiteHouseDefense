#include <assert.h>
#include "../../common/Constants.h"
#include "../../common/Message.hpp"
#include "ProfileManager.hpp"
#include "ProfileGUI.hpp"
#include "ProfileConsoleUI.hpp"


ProfileManager::ProfileManager(int port, App *my_app) :
        NetworkedManager(port, my_app) {
    if (false && !isConsole) {
        profileUI = new ProfileGUI(this);
    } else {
        profileUI = new ProfileConsoleUI(this);
    }
}

void ProfileManager::run() {
    profileUI->display();
}

void ProfileManager::showMyProfile() {
    getAndParseProfile(master_app->get_username());
    profileUI->displayProfile();
}

void ProfileManager::showProfile() {
    std::string profile = profileUI->getUsername();
    getAndParseProfile(profile);

    if (username == "") { // No such profile
        profileUI->displayNoSuchProfileError();
    } else {
        profileUI->displayProfile();
    }
}

void ProfileManager::goToMainMenu() {
    MainManager *mainManager = new MainManager(ACCOUNT_SERVER_PORT, master_app);
    master_app->transition(mainManager);
}

void ProfileManager::getAndParseProfile(std::string username) {
    std::string message = GET_PROFILE + username + ";";
    send_message(server_socket, message.c_str());
    char buffer[MAX_BUFF_SIZE];
    receive_message(server_socket, buffer);
    parseProfileData(buffer);
}

std::string ProfileManager::getPlayerUsername() {
    return master_app->get_username();
}

void ProfileManager::parseProfileData(char *profileData) {
    Message message;
    message.setData(profileData);

    username = message.getNextToken();

    if (username != "") { /* If the response isn't empty, the profile exists */
        victories = std::stoi(message.getNextToken());
        npcKilled = std::stoi(message.getNextToken());
        assert(message.hasReachedEnd());
    }
}

int ProfileManager::getVictories() const {
    return victories;
}

int ProfileManager::getNPCKilled() const {
    return npcKilled;
}

std::string &ProfileManager::getUsername() {
    return username;
}


