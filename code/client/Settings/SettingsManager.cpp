#include "SettingsManager.hpp"
#include "../../common/Constants.h"
#include "SettingsGUI.hpp"
#include "SettingsConsoleUI.hpp"

SettingsManager::SettingsManager (int port, App *my_app) :
        NetworkedManager(port, my_app), username("Loading..."), password("Loading..."), iconName("Loading...") {
    if (!isConsole) {
        settingsUI = new SettingsGUI(this, master_app->getMainWindow());
    } else {
        //settingsUI = new SettingsConsoleUI(this);
    }

}

void SettingsManager::run() {
    settingsUI->display();
}

void SettingsManager::changeUsername(std::string newUsername){
    std::string message = CHANGE_USERNAME + ',' + std::to_string(master_app->get_id()) + ',' + newUsername + ';';
    send_message(server_socket, message.c_str());
}

void SettingsManager::changePassword(std::string newPassword){
    std::string message = CHANGE_PASSWORD + ',' + std::to_string(master_app->get_id()) + ',' + newPassword + ';';
    send_message(server_socket, message.c_str());

}

void SettingsManager::changePlayerIcon(std::string newIconName){
    std::string message = CHANGE_ICON + ',' + std::to_string(master_app->get_id()) + ',' + newIconName + ';';
    send_message(server_socket, message.c_str());

}

void SettingsManager::goToMainMenu() {
    MainManager * mainManager = new MainManager(ACCOUNT_SERVER_PORT, master_app);
    master_app->transition(mainManager);
}