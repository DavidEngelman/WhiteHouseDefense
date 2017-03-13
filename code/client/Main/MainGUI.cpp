#include "MainGUI.hpp"
#include <QtCore/QFile>
#include <QtWidgets/QFormLayout>
#include <QtMultimedia/QMediaPlayer>

MainGUI::MainGUI(MainManager *manager) : MainUI(manager) {}

void MainGUI::display() {
    QFile File("../../qt_ui/americanLogin.qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(styleSheet);

    //this->setFixedHeight(600);
    //this->setFixedWidth(750);
    //QPixmap bkgnd("../../qt_ui/game_pictures/backgrounds/Whitehouse");
    //bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setColor(QPalette::Background,QColor::fromRgb(0,0,80));//faut trouver la bonne couleur
    this->setPalette(palette);
    QFont police("calibri");

    QFrame * fields = new QFrame(this);
    QFormLayout * fieldsLayout = new QFormLayout(this);

    QString s1 = "NEW GAME";
    QString s2 = "SPECTATOR";
    QString s3 = "PROFILE";
    QString s4 = "FRIEND LIST";
    QString s5 = "LEADERBOARD";
    QString s6 = "EXIT";

    newGame = new QCustomButton(1, s1,fields);
    newGame->setFixedSize(QSize(212,45));

    spectator = new QCustomButton(2, s2,fields);
    spectator->setFixedSize(QSize(212,45));

    profile = new QCustomButton(3, s3,fields);
    profile->setFixedSize(QSize(212,45));

    friendList = new QCustomButton(4, s4,fields);
    friendList->setFixedSize(QSize(212,45));

    leaderBoard = new QCustomButton(5, s5,fields);
    leaderBoard->setFixedSize(QSize(212,45));

    exit = new QCustomButton(6, s6,fields);
    exit->setFixedSize(QSize(212,45));

    QObject::connect(newGame, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(spectator, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(profile, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(friendList, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(leaderBoard, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(exit, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));

    fieldsLayout->addRow(newGame);
    fieldsLayout->addRow(spectator);
    fieldsLayout->addRow(profile);
    fieldsLayout->addRow(friendList);
    fieldsLayout->addRow(leaderBoard);
    fieldsLayout->addRow(exit);
    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 125, this->size().height() / 2 +105);

    this->showMaximized();
}

void MainGUI::displayGameModesMenu() {
    // TODO: lui proposer le choix
    QFile File("../../qt_ui/americanLogin.qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(styleSheet);

    QPalette palette;
    palette.setColor(QPalette::Background,QColor::fromRgb(0,0,80));//faut trouver la bonne couleur
    this->setPalette(palette);
    QFont police("calibri");

    QFrame * fields = new QFrame(this);
    QFormLayout * fieldsLayout = new QFormLayout(this);
    QString s1 = "NEW GAME";
    QString s2 = "SPECTATOR";
    QString s3 = "PROFILE";

    newGame = new QCustomButton(1, s1,fields);
    newGame->setFixedSize(QSize(212,45));

    spectator = new QCustomButton(2, s2,fields);
    spectator->setFixedSize(QSize(212,45));

    profile = new QCustomButton(3, s3,fields);
    profile->setFixedSize(QSize(212,45));

    QObject::connect(newGame, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(spectator, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(profile, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));

    fieldsLayout->addRow(newGame);
    fieldsLayout->addRow(spectator);
    fieldsLayout->addRow(profile);
    fieldsLayout->addRow(friendList);
    fieldsLayout->addRow(leaderBoard);
    fieldsLayout->addRow(exit);
    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 125, this->size().height() / 2 +105);

    this->showMaximized();
    // créer un slot qui fera appel à handleGameModeChoice
}

void MainGUI::handleMenuChoice(int choice) {
    std::cout << choice << std::endl;
    menuChoice = choice;
    manager->handleUserMenuChoice();
}

void MainGUI::handleGameModeChoice(){
    // TODO: gameModeChoice = le choix de l'utilisateur;
    manager->handleGameModeChoice();
}