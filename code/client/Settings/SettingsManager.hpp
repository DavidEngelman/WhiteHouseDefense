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

    bool changeUsername(std::string newUsername);
    bool changePassword(std::string newPassword);
    void changePlayerIcon(std::string newIconName);
    void goToMainMenu();

    void comeBackToMainMenu();

    ~SettingsManager();
};


#endif //PROJET_SETTINGSMANAGER_HPP
