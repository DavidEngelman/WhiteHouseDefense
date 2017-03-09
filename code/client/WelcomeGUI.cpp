//
// Created by jepsiko on 09/03/17.
//

#include <iostream>
#include <QtWidgets/QFrame>
#include <QCoreApplication>
#include "WelcomeGUI.hpp"

WelcomeGUI::WelcomeGUI(QWidget *parent) : QWidget(parent){}


void WelcomeGUI::setupGUI() {
    setTheme();

    QFrame * fields = new QFrame(this);
    fieldsLayout = new QFormLayout;

    loginButton = new QPushButton("LOGIN", fields);
    loginButton->setFixedSize(QSize(212,45));
    connect(loginButton, SIGNAL (released()), this, SLOT (openLogin()));

    registerButton = new QPushButton("REGISTER", fields);
    registerButton->setFixedSize(QSize(212,45));
    connect(registerButton, SIGNAL (released()), this, SLOT (openRegister()));

    quitButton = new QPushButton("QUIT", fields);
    quitButton->setFixedSize(QSize(212,45));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    fieldsLayout->addRow(loginButton);
    fieldsLayout->addRow(registerButton);
    fieldsLayout->addRow(quitButton);


    this->setLayout(fieldsLayout);
    this->show();
}

void WelcomeGUI::openWindow() {
    std::cout << "opening window" << std::endl;
}
void WelcomeGUI::openLogin(){
    std::cout << "Login!" << std::endl;

}
void WelcomeGUI::openRegister(){
    std::cout << "Register" << std::endl;

}

void WelcomeGUI::setTheme() {
    QFile File;
    QString styleSheet;
    QPixmap bkgnd;
    QPalette palette;
    QMediaPlayer *player = new QMediaPlayer;

    File.setFileName("../../qt_ui/americanMain.qss");
    File.open(QFile::ReadOnly);
    styleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(styleSheet);
    this->setFixedHeight(600);
    this->setFixedWidth(750);
    bkgnd = QPixmap("../../qt_ui/game_pictures/backgrounds/americanBg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    player->setMedia(QUrl::fromLocalFile("../../qt_ui/game_pictures/sounds/americanAnthem.mp3"));
    player->setVolume(100);
    player->play();
}

WelcomeGUI::~WelcomeGUI(){

}