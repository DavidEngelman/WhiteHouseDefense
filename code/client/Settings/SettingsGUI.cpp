#include "SettingsGUI.hpp"
#include "SettingsManager.hpp"
#include "IconSelectionWidget.hpp"

SettingsGUI::SettingsGUI(SettingsManager *manager, QWidget* _parent) : AbstractGUI(_parent), SettingsUI(manager),
                                                                       changedIcon(false) {}

void SettingsGUI::display() {
    QElapsedTimer timer;
    timer.start();


    this->setFixedHeight(600);
    this->setFixedWidth(1000);

    /* Set background */
    setBackgroundFromPath("../../qt_ui/game_pictures/backgrounds/trump_background.png");

    /* Layouts */

    QVBoxLayout * boxLayout = new QVBoxLayout;
    QHBoxLayout * topLayout = new QHBoxLayout;
    buttonsLayout = new QVBoxLayout;


    /* Home Button*/
    QHandPointerButton* homeButton = new QHandPointerButton("HOME", 70, 35, this);
    homeButton->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::Preferred );
    homeButton->setStyleSheet("border-image:url(../../qt_ui/game_pictures/buttons/gold_button_2.svg);");
    QObject::connect(homeButton, SIGNAL(clicked()), this, SLOT(goToMain()));
    topLayout->addWidget(homeButton);
    topLayout->addStretch();

    topLayout->setAlignment(homeButton, Qt::AlignLeft);

    /* Title */
    QLabel* title = new QLabel("Settings");
    title->setSizePolicy( QSizePolicy::Maximum, QSizePolicy::Preferred );
    title->setStyleSheet("color: gold;  font-size: 27pt;  font-weight: bold");
    topLayout->addWidget(title);
    topLayout->addStretch();

    topLayout->setAlignment(title, Qt::AlignLeft);

    /*Menu*/
    usernameB = new QHandPointerButton("Change Username", 300,40);
    usernameB->setStyleSheet("border-image:url(../../qt_ui/game_pictures/buttons/gold_button_2.svg);");

    passwordB = new QHandPointerButton("Change Password", 300,40);
    passwordB->setStyleSheet("border-image:url(../../qt_ui/game_pictures/buttons/gold_button_2.svg);");

    iconB = new QHandPointerButton("Change icon", 300,40);
    iconB->setStyleSheet("border-image:url(../../qt_ui/game_pictures/buttons/gold_button_2.svg);");

    buttonsLayout->addWidget(usernameB);
    buttonsLayout->addWidget(passwordB);
    buttonsLayout->addWidget(iconB);
    buttonsLayout->setSpacing(30);

    boxLayout->addLayout(topLayout);
    boxLayout->addStretch();
    boxLayout->addLayout(buttonsLayout);
    boxLayout->addStretch();
    boxLayout->setAlignment(topLayout, Qt::AlignTop);
    boxLayout->setAlignment(buttonsLayout, Qt::AlignTop|Qt::AlignHCenter);

    QObject::connect(iconB, SIGNAL(clicked()), this, SLOT(openIconSelectionWidget()));
    QObject::connect(usernameB, SIGNAL(clicked()), this, SLOT(changeUsername()));
    QObject::connect(passwordB, SIGNAL(clicked()), this, SLOT(changePassword()));


    this->setLayout(boxLayout);

    std::cout << "It took " << timer.nsecsElapsed() / 1000000000.0 << " seconds for SettingsGUI::display" << std::endl;
    this->show();
}



void SettingsGUI::openIconSelectionWidget(){
    IconSelectionWidget* widget = new IconSelectionWidget(this);
}

void SettingsGUI::goToMain() {
    settingsManager->goToMainMenu();
}

void SettingsGUI::handleIconChange(int icon){
    newIconName = std::to_string(icon);
    changedIcon = true;
}

void SettingsGUI::changeUsername(){
    usernameB->setVisible(false);
    lineEditU = new QLineEdit();
    lineEditU->setFixedSize(300,40);
    QObject::connect(lineEditU, SIGNAL(returnPressed()), this, SLOT(applyUsernameChange()));
    lineEditU->setPlaceholderText("New username");
    buttonsLayout->insertWidget(0, lineEditU);
}

void SettingsGUI::changePassword(){
    QElapsedTimer timer;
    timer.start();
    passwordB->setVisible(false);
    lineEditP = new QLineEdit();
    lineEditP->setFixedSize(300,40);
    lineEditP->setPlaceholderText("New Password");
    QObject::connect(lineEditP, SIGNAL(returnPressed()), this, SLOT(applyPasswordChange()));

    buttonsLayout->insertWidget(1, lineEditP);
    std::cout << "It took " << timer.nsecsElapsed() / 1000000000.0 << " seconds for SettingsGUI::changePassword" << std::endl;
}

void SettingsGUI::applyUsernameChange(){
    std::string lineEditContent = lineEditU->text().toStdString();
    std::cout << lineEditContent << std::endl;

    if(!settingsManager->changeUsername(lineEditContent)){
        QMessageBox::critical(this, "Invalid username", "Error: Username invaild or already taken");
    } else {
        std::string message = "Your Username has been changed and is now: " +  lineEditContent + " ";
        QMessageBox::information(this, "Success", QString::fromStdString(message));
        lineEditU->setVisible(false);
        usernameB->setVisible(true);

    }
    lineEditU->clear();

}

void SettingsGUI::applyPasswordChange(){
    std::string lineEditContent = lineEditP->text().toStdString();
    std::cout << lineEditContent << std::endl;
    if(!settingsManager->changePassword(lineEditContent)){
        QMessageBox::critical(this, "Invalid password", "Error: Invalid password");
    } else {
        std::string message = "Your password has been changed and is now: " +  lineEditContent + " ";
        QMessageBox::information(this, "Success", QString::fromStdString(message));
        lineEditP->setVisible(false);
        passwordB->setVisible(true);

    }
    lineEditP->clear();
}

void SettingsGUI::applyIconChange(std::string iconName){
    settingsManager->changePlayerIcon(iconName);
    QMessageBox::information(this, "Success", "Your icon has been changed !");
}

void SettingsGUI::hideButton(){
    usernameB->setVisible(false);
}


