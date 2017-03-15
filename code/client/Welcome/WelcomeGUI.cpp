#include <QtWidgets/QFrame>
#include <QCoreApplication>
#include <QtCore/QFileInfo>
#include <QtMultimedia/QMediaPlaylist>
#include "WelcomeGUI.hpp"
#include "WelcomeManager.hpp"


void WelcomeGUI::display() {
    setTheme();

    QFrame * fields = new QFrame(this);
    fieldsLayout = new QFormLayout;

    loginButton = new QPushButton("LOGIN", fields);
    loginButton->setFixedSize(QSize(212,45));
    loginButton->setCursor(Qt::PointingHandCursor);
    connect(loginButton, SIGNAL (released()), this, SLOT (openLogin()));

    registerButton = new QPushButton("REGISTER", fields);
    registerButton->setFixedSize(QSize(212,45));
    registerButton->setCursor(Qt::PointingHandCursor);
    connect(registerButton, SIGNAL (released()), this, SLOT (openRegister()));

    quitButton = new QPushButton("QUIT", fields);
    quitButton->setFixedSize(QSize(212,45));
    quitButton->setCursor(Qt::PointingHandCursor);
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

WelcomeGUI::WelcomeGUI(WelcomeManager *manager) : manager(manager) {}
