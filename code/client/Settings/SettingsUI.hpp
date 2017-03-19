#ifndef PROJET_SETTINGSUI_HPP
#define PROJET_SETTINGSUI_HPP


#include "../Abstract/AbstractUI.hpp"
class SettingsManager;


class SettingsUI : public virtual AbstractUI{

protected:
    SettingsManager *settingsManager;

public:

    SettingsUI(SettingsManager *_settingsManager) : settingsManager(_settingsManager) {};
    virtual std::string display() = 0;
    virtual std::string getNewUsername() = 0;
    virtual std::string getNewPassword() = 0;
    virtual std::string getNewIconName() = 0;

};


#endif //PROJET_SETTINGSUI_HPP
