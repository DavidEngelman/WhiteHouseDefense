#include "SettingsGUI.hpp"
#include "SettingsManager.hpp"
SettingsGUI::SettingsGUI(SettingsManager *manager, QWidget* _parent) : AbstractGUI(_parent), SettingsUI(manager) {}

void SettingsGUI::display() {

    this->setFixedHeight(600);
    this->setFixedWidth(1000);

    /* Set background */
    setBackgroundFromPath("../../qt_ui/game_pictures/backgrounds/trump_background.png");

    QHBoxLayout * mainLayout = new QHBoxLayout;
    QVBoxLayout * boxLayout = new QVBoxLayout;
    QFormLayout * fieldsLayout = new QFormLayout();

    usernameL = new QLineEdit();
    usernameL->setFixedWidth(300);
    passwordL = new QLineEdit();
    passwordL->setFixedWidth(300);
    iconB = new QHandPointerButton("Change icon", 300,20);
    updateB = new QHandPointerButton("Update profile",300,20);

    QLabel *usernameT = new QLabel("USERNAME: ");
    QLabel *passwordT = new QLabel("PASSWORD: ");
    QLabel *iconT = new QLabel("ICON: ");
    usernameT->setStyleSheet("color : white;");
    passwordT->setStyleSheet("color : white;");
    iconT->setStyleSheet("color : white;");

    fieldsLayout->addRow(usernameT, usernameL);
    fieldsLayout->addRow(passwordT, passwordL);
    fieldsLayout->addRow(iconT, iconB);
    boxLayout->addLayout(fieldsLayout);
    boxLayout->addWidget(updateB);
    boxLayout->setAlignment(updateB, Qt::AlignCenter);
    boxLayout->setAlignment(fieldsLayout, Qt::AlignCenter);

    this->setLayout(boxLayout);
    this->show();

    QObject::connect(updateB, SIGNAL(clicked()), this, SLOT(updateProfile()));
}

void SettingsGUI::updateProfile(){
    std::string usernameLContent= usernameL->text().toStdString();
    std::string passwordLContent= passwordL->text().toStdString();

    if (usernameLContent != "") {
        settingsManager->changeUsername(usernameLContent);
    } if (passwordLContent != "") {
        settingsManager->changePassword(passwordLContent);
    } if (changedIcon) {
        settingsManager->changePlayerIcon(newIconName);
    }

}

