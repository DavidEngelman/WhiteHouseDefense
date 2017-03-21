#ifndef PROJET_SETTINGSUI_HPP
#define PROJET_SETTINGSUI_HPP


#include "../Abstract/AbstractUI.hpp"
class SettingsManager;


class SettingsUI : public virtual AbstractUI {

protected:
    SettingsManager *settingsManager;

public:

    SettingsUI(SettingsManager *_settingsManager) : settingsManager(_settingsManager) {};
    virtual void display() = 0;

    virtual ~SettingsUI() = default;

};


#endif //PROJET_SETTINGSUI_HPP
