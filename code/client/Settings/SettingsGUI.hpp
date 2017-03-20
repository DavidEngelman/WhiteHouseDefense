//
//

#ifndef PROJET_SETTINGSGUI_HPP
#define PROJET_SETTINGSGUI_HPP


#include "../Abstract/AbstractGUI.hpp"
#include "SettingsUI.hpp"
#include "../QHandPointerButton.hpp"

class SettingsGUI : public AbstractGUI, public SettingsUI {
Q_OBJECT

private:


    QLineEdit *usernameL;
    QLineEdit *passwordL;
    QHandPointerButton *iconB;

    std::string newIconName;

    QHandPointerButton *updateB;

    bool changedIcon;


public:

    SettingsGUI(SettingsManager *manager, QWidget* _parent);

    void display() override;

    void updateProfile();
};


#endif //PROJET_SETTINGSGUI_HPP
