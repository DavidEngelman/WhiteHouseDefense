#include "SettingsGUI.hpp"
#include "SettingsManager.hpp"
SettingsGUI::SettingsGUI(SettingsManager *manager, QWidget* _parent) : AbstractGUI(_parent), SettingsUI(manager),
                                                                       changedIcon(false) {}

void SettingsGUI::display() {

    this->setFixedHeight(600);
    this->setFixedWidth(1000);

    /* Set background */
    setBackgroundFromPath("../../qt_ui/game_pictures/backgrounds/trump_background.png");

    QVBoxLayout * boxLayout = new QVBoxLayout;
    QVBoxLayout * fieldsLayout = new QVBoxLayout;

    QLabel* title = new QLabel("Settings");
    title->setStyleSheet("color: gold;  font-size: 27pt; font-weight: bold");

    QHandPointerButton* homeButton = new QHandPointerButton("HOME", 70, 35, this);
    homeButton->setStyleSheet("border-image:url(../../qt_ui/game_pictures/buttons/gold_button_2.svg);");
    QObject::connect(homeButton, SIGNAL(clicked()), this, SLOT(goToMain()));

    boxLayout->addWidget(homeButton);
    boxLayout->setAlignment(homeButton, Qt::AlignLeft|Qt::AlignTop);

    usernameL = new QLineEdit();
    usernameL->setFixedWidth(300);
    passwordL = new QLineEdit();
    passwordL->setFixedWidth(300);

    iconB = new QHandPointerButton("Change icon", 300,40);

    updateB = new QHandPointerButton("Update profile",150,25);


    QLabel *usernameT = new QLabel("Username: ");
    QLabel *passwordT = new QLabel("Password: ");
    QLabel *iconT = new QLabel("Icon: ");
    usernameT->setStyleSheet("color : gold;");
    passwordT->setStyleSheet("color : gold; padding-top:30;");
    iconT->setStyleSheet("color : gold; padding-top:30;");


    fieldsLayout->addWidget(usernameT);
    fieldsLayout->addWidget(usernameL);

    fieldsLayout->addWidget(passwordT);
    fieldsLayout->addWidget(passwordL);

    fieldsLayout->addWidget(iconT);
    fieldsLayout->addWidget(iconB);

    boxLayout->addWidget(title);
    boxLayout->addLayout(fieldsLayout);
    boxLayout->addWidget(updateB);

    boxLayout->setAlignment(title, Qt::AlignCenter);
    boxLayout->setAlignment(updateB, Qt::AlignCenter);
    boxLayout->setAlignment(fieldsLayout, Qt::AlignCenter);

    this->setLayout(boxLayout);
    this->show();

    QObject::connect(updateB, SIGNAL(clicked()), this, SLOT(updateProfile()));
}

void SettingsGUI::updateProfile(){
    bool success = true;

    std::string usernameLContent= usernameL->text().toStdString();
    std::string passwordLContent= passwordL->text().toStdString();

    if (usernameLContent != "") {
        std::cout << usernameLContent << std::endl;
        if(!settingsManager->changeUsername(usernameLContent)){
            QMessageBox::critical(this, "Invalid username", "Error: Username invaild or already taken");
            success = false;
        }

    } if (passwordLContent != "") {

        if(!settingsManager->changePassword(passwordLContent)){
            QMessageBox::critical(this, "Invalid password", "Error: Invalid password");
            success = false;
        }

    } if (changedIcon) {
        settingsManager->changePlayerIcon(newIconName);
    }


    if (success){
        QMessageBox::information(this, "Success", "Your informations have been updated !");
    }
    usernameL->clear();
    passwordL->clear();



}

void SettingsGUI::goToMain() {
    settingsManager->goToMainMenu();
}

