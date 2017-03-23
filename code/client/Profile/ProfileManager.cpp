#include <assert.h>
#include "../../common/Other/Constants.hpp"
#include "../../common/Other/Message.hpp"
#include "ProfileManager.hpp"
#include "ProfileGUI.hpp"
#include "ProfileConsoleUI.hpp"


ProfileManager::ProfileManager(int port, App *my_app) :
        NetworkedManager(port, my_app), username("Loading..."), victories(-1), npcKilled(-1) {
    if (!isConsole) {
        profileUI = new ProfileGUI(this, master_app->getMainWindow());
    } else {
        profileUI = new ProfileConsoleUI(this);
    }

}

void ProfileManager::run() {
    profileUI->display();
    showMyProfile();
}

void ProfileManager::showMyProfile() {
    getAndParseProfile(master_app->getUsername());
    profileUI->updateProfile();
}

void ProfileManager::showProfile() {
    std::string profile = profileUI->getUsername();
    getAndParseProfile(profile);

    if (username == "") { // No such profile
        profileUI->displayNoSuchProfileError();
    } else {
        profileUI->updateProfile();
    }
}

void ProfileManager::getAndParseProfile(std::string username) {
    std::string message = GET_PROFILE + username + ";";
    send_message(server_socket, message.c_str());
    char buffer[MAX_BUFF_SIZE];
    receive_message(server_socket, buffer);
    parseProfileData(buffer);
}

void ProfileManager::parseProfileData(char *profileData) {
    Message message;
    message.setData(profileData);

    username = message.getNextToken();

    if (username != "") { /* If the response isn't empty, the profile exists */
        victories = std::stoi(message.getNextToken());
        defeats = std::stoi(message.getNextToken());
        npcKilled = std::stoi(message.getNextToken());
        iconID = std::stoi(message.getNextToken());

        assert(message.hasReachedEnd());
    }
}

int ProfileManager::getVictories() const {
    return victories;
}

int ProfileManager::getDefeats() const {
    return defeats;
}

int ProfileManager::getNPCKilled() const {
    return npcKilled;
}

std::string &ProfileManager::getUsername() {
    return username;
}

int ProfileManager::getIconID() const {
    return iconID;
}

ProfileManager::~ProfileManager() {
    profileUI->destroy();

}

void ProfileManager::goToMainMenu() {
    MainManager * mainManager = new MainManager(ACCOUNT_SERVER_PORT, master_app);
    master_app->transition(mainManager);
}


