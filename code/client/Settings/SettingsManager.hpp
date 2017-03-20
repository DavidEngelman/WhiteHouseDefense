#ifndef PROJET_SETTINGSMANAGER_HPP
#define PROJET_SETTINGSMANAGER_HPP


#include "../NetworkedManager.hpp"
#include "SettingsUI.hpp"
#include "../Main/MainManager.hpp"
#include "../App.hpp"

class SettingsManager : public NetworkedManager{

private:

    SettingsUI * settingsUI;

    std::string username;
    std::string password;
    std::string iconName;

public:

    SettingsManager(int port, App* my_app);

    void run();

    void changeUsername(std::string newUsername);
    void changePassword(std::string newPassword);
    void changePlayerIcon(std::string newIconName);
    void goToMainMenu();
};


#endif //PROJET_SETTINGSMANAGER_HPP
