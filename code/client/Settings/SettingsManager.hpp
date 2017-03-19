#ifndef PROJET_SETTINGSMANAGER_HPP
#define PROJET_SETTINGSMANAGER_HPP


#include "../NetworkedManager.hpp"
#include "SettingsUI.hpp"
#include "../Main/MainManager.hpp"
#include "../App.hpp"

class SettingsManager : NetworkedManager{

private:

    SettingsUI * settingsUI;

    std::string username;
    std::string password;
    std::string iconName;

public:

    SettingsManager(int port, App* my_app);

    void run();

    void changeUsername();
    void changePassword();
    void changePlayerIcon();
    void goToMainMenu();
};


#endif //PROJET_SETTINGSMANAGER_HPP
