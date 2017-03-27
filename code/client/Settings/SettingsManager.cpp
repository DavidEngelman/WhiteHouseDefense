#include "SettingsManager.hpp"
#include "SettingsGUI.hpp"
#include "../../common/Other/Strings.hpp"
#include "../../common/Other/Tools.hpp"
#include "../../common/Other/Constants.hpp"

SettingsManager::SettingsManager (int port, App *my_app) :
        NetworkedManager(port, my_app) {
    if (!isConsole) {
        settingsUI = new SettingsGUI(this, master_app->getMainWindow());
    } else {
        //settingsUI = new SettingsConsoleUI(this);
    }

}

void SettingsManager::run() {
    settingsUI->display();
}

bool SettingsManager::changeUsername(std::string newUsername){
    if (newUsername.size() < 1 || newUsername.size() > 16){
        return false;
    }
    char server_response[10];
    std::string message = CHANGE_USERNAME + ',' + std::to_string(master_app->getId()) + ',' + newUsername + ';';
    send_message(server_socket, message.c_str());
    receive_message(server_socket, server_response);
    master_app->setUsername(newUsername); //important
    return server_response[0] == '1';

}

bool SettingsManager::changePassword(std::string newPassword){
    if (newPassword.size() < 1){
        return false;
    }
    newPassword = cryptPassword(newPassword);
    std::string message = CHANGE_PASSWORD + ',' + std::to_string(master_app->getId()) + ',' + newPassword + ';';
    send_message(server_socket, message.c_str());
    return true;

}

void SettingsManager::changePlayerIcon(std::string newIconName){
    std::string message = CHANGE_ICON + ',' + std::to_string(master_app->getId()) + ',' + newIconName + ';';
    send_message(server_socket, message.c_str());

}

void SettingsManager::goToMainMenu() {
    MainManager * mainManager = new MainManager(ACCOUNT_SERVER_PORT, master_app);
    master_app->transition(mainManager);
}

SettingsManager::~SettingsManager() {
    settingsUI->destroy();
}
