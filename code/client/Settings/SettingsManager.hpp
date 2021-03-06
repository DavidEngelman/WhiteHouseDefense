#ifndef PROJET_SETTINGSMANAGER_HPP
#define PROJET_SETTINGSMANAGER_HPP


#include "../Other/NetworkedManager.hpp"
#include "SettingsUI.hpp"
#include "../Main/MainManager.hpp"
#include "../Other/App.hpp"

class SettingsManager : public NetworkedManager{

private:

    SettingsUI * settingsUI;

public:

    SettingsManager(int port, App* my_app);

    void run();

    bool changeUsername(std::string newUsername);
    bool changePassword(std::string newPassword);
    void changePlayerIcon(std::string newIconName);
    void goToMainMenu();


    ~SettingsManager();
};


#endif //PROJET_SETTINGSMANAGER_HPP
