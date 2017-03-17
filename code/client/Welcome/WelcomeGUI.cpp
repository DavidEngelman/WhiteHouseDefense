#include <QtWidgets/QFrame>
#include <QCoreApplication>
#include <QtCore/QFileInfo>
#include <QtMultimedia/QMediaPlaylist>
#include "WelcomeGUI.hpp"
#include "WelcomeManager.hpp"
#include "../QHandPointerButton.hpp"


void WelcomeGUI::display() {
    setTheme();

    QFrame * fields = new QFrame(this);
    fieldsLayout = new QFormLayout;

    loginButton = new QHandPointerButton("LOGIN", 212, 45, fields);
    connect(loginButton, SIGNAL (clicked()), this, SLOT (openLogin()));

    registerButton = new QHandPointerButton("REGISTER", 212, 45, fields);
    connect(registerButton, SIGNAL (clicked()), this, SLOT (openRegister()));

    quitButton = new QHandPointerButton("QUIT", 212, 45, fields);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    

    fieldsLayout->addRow(loginButton);
    fieldsLayout->addRow(registerButton);
    fieldsLayout->addRow(quitButton);

    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 125, this->size().height() / 2 +100);

    this->show();
}

void WelcomeGUI::openLogin(){
    manager->goToLogin();
}

void WelcomeGUI::openRegister(){
    manager->goToRegister();
}

void WelcomeGUI::setTheme() {

    this->setFixedHeight(600);
    this->setFixedWidth(750);

    setStylesheetFromPath("../../qt_ui/americanMain.qss");
    setBackgroundFromPath("../../qt_ui/game_pictures/backgrounds/americanBg");
    setMusicFromPath("../../qt_ui/game_pictures/sounds/americanAnthem.mp3");

}

WelcomeGUI::~WelcomeGUI() {
    close();
}

WelcomeGUI::WelcomeGUI(WelcomeManager *manager, QWidget* _parent) : AbstractGUI(_parent), manager(manager) {}
