#include <iostream>
#include <QtWidgets/QFrame>
#include <QCoreApplication>
#include <QtCore/QFileInfo>
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
    QFile File;
    QString styleSheet;
    QPixmap bkgnd;
    QPalette palette;
    QMediaPlayer *player = new QMediaPlayer(this);

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
    player->setMedia(QUrl::fromLocalFile(QFileInfo("../../qt_ui/game_pictures/sounds/americanAnthem.mp3").absoluteFilePath()));
    player->setVolume(100);
    player->play();
}

WelcomeGUI::~WelcomeGUI() {
    close();
    std::cout << "Welcome GUI closed." << std::endl;
}

WelcomeGUI::WelcomeGUI(WelcomeManager *manager) : manager(manager) {}
