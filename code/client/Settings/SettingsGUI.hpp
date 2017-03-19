//
//

#ifndef PROJET_SETTINGSGUI_HPP
#define PROJET_SETTINGSGUI_HPP


#include "../Abstract/AbstractGUI.hpp"
#include "SettingsUI.hpp"

class SettingsGUI : public AbstractGUI, public SettingsUI {
Q_OBJECT

private:

public:

    SettingsGUI(SettingsManager *manager, QWidget* _parent);

    void display() override;
    std::string getNewUsername();
    std::string getNewPassword();
    std::string getNewIconName();
};


#endif //PROJET_SETTINGSGUI_HPP
