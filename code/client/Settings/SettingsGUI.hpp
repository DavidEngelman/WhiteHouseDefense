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
    QHandPointerButton *usernameB;
    QHandPointerButton *passwordB;

    std::string newIconName;

    QHandPointerButton *updateB;

    bool changedIcon;

    QVBoxLayout * buttonsLayout;
    QLineEdit *lineEditU;
    QLineEdit *lineEditP;


public:

    SettingsGUI(SettingsManager *manager, QWidget* _parent);

    void display() override;

public slots:

    void goToMain();
    void openIconSelectionWidget();

    void handleIconChange(int icon);
    void changeUsername();
    void changePassword();

    void applyUsernameChange();
    void applyPasswordChange();
    void applyIconChange(std::string iconName);

    void hideButton();
};


#endif //PROJET_SETTINGSGUI_HPP
