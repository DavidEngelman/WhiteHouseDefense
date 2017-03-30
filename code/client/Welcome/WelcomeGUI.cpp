#include <QtWidgets/QFrame>
#include <QCoreApplication>
#include <QtMultimedia/QMediaPlaylist>
#include "WelcomeGUI.hpp"
#include "../Other/QHandPointerButton.hpp"

WelcomeGUI::WelcomeGUI(WelcomeManager *manager, QWidget *_parent) : AbstractGUI(_parent), WelcomeUI(manager) {}

void WelcomeGUI::display() {

    setTheme();

    QFrame *fields = new QFrame(this);
    fieldsLayout = new QFormLayout;

    loginButton = new QHandPointerButton("LOGIN", 212, 45, fields);
    connect(loginButton, SIGNAL (clicked()), this, SLOT (openLogin()));

    registerButton = new QHandPointerButton("REGISTER", 212, 45, fields);
    connect(registerButton, SIGNAL (clicked()), this, SLOT (openRegister()));

    quitButton = new QHandPointerButton("QUIT", 212, 45, fields);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(quit()));


    fieldsLayout->addRow(loginButton);
    fieldsLayout->addRow(registerButton);
    fieldsLayout->addRow(quitButton);

    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 125, this->size().height() / 2 + 100);

    manager->setMusicFromPath("../../qt_ui/resources/sounds/americanAnthem.mp3");
    this->show();
    AbstractGUI::parent->show();
    // On affiche la fenetre principale qu'à partir du moment ou WelcomeGUI est pret pour que ce soit plus smooth
}

void WelcomeGUI::openLogin() {
    manager->goToLogin();
}

void WelcomeGUI::openRegister() {
    manager->goToRegister();
}

void WelcomeGUI::setTheme() {

    this->setFixedHeight(600);
    this->setFixedWidth(750);

    setStylesheetFromPath("../../qt_ui/americanMain.qss");
    setBackgroundFromPath("../../qt_ui/resources/backgrounds/americanBg");
}

void WelcomeGUI::quit(){
    exit(0);

}

WelcomeGUI::~WelcomeGUI() {}

