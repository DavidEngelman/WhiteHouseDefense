#include "SettingsManager.hpp"
#include "../../common/Constants.h"

SettingsManager::SettingsManager (int port, App *my_app) :
        NetworkedManager(port, my_app), username("Loading..."), password("Loading..."), iconName("Loading...") {
    if (!isConsole) {
        settingsUI = new SettingsUI(this, master_app->getMainWindow());
    } else {
        settingsUI = new SettingsUI(this);
    }

}

void SettingsManager::run() {
    settingsUI->display();
}

void SettingsManager::changeUsername(){
    std::string newUserName = settingsUI->getNewUsername();
    std::string message = CHANGE_USERNAME + ',' + master_app->get_username() + ',' + newUserName + ';';
}

void SettingsManager::changePassword(){
    std::string newPassword = settingsUI->getNewPassword();
    std::string message = CHANGE_PASSWORD + ',' + master_app->get_username() + ',' + newPassword + ';';
}

void SettingsManager::changePlayerIcon(){
    std::string newIconName = settingsUI->getNewIconName();
    std::string message = CHANGE_ICON + ',' + master_app->get_username() + ',' + newIconName + ';';
}

void SettingsManager::goToMainMenu() {
    MainManager * mainManager = new MainManager(ACCOUNT_SERVER_PORT, master_app);
    master_app->transition(mainManager);
}