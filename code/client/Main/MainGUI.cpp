#include "MainGUI.hpp"
#include <QtCore/QFile>
#include <QtWidgets/QFormLayout>
#include <QtMultimedia/QMediaPlayer>
#include <QtWidgets/QDialogButtonBox>


MainGUI::MainGUI(MainManager *manager) : MainUI(manager) {}

void MainGUI::display() {

    this->setFixedHeight(600);
    this->setFixedWidth(1000);

    QFile File("../../qt_ui/americanLogin.qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(styleSheet);

    setBackgroundFromPath("../../qt_ui/game_pictures/backgrounds/whitehouse_bckgrd.png");


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
    newGame->setCursor(Qt::PointingHandCursor);
    newGame->setFixedSize(QSize(212,45));

    spectator = new QCustomButton(2, s2,fields);
    spectator->setCursor(Qt::PointingHandCursor);
    spectator->setFixedSize(QSize(212,45));

    profile = new QCustomButton(3, s3,fields);
    profile->setCursor(Qt::PointingHandCursor);
    profile->setFixedSize(QSize(212,45));

    friendList = new QCustomButton(4, s4,fields);
    friendList->setCursor(Qt::PointingHandCursor);
    friendList->setFixedSize(QSize(212,45));

    leaderBoard = new QCustomButton(5, s5,fields);
    leaderBoard->setCursor(Qt::PointingHandCursor);
    leaderBoard->setFixedSize(QSize(212,45));

    QObject::connect(newGame, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(spectator, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(profile, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(friendList, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(leaderBoard, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));

    fieldsLayout->addRow(newGame);
    fieldsLayout->addRow(spectator);
    fieldsLayout->addRow(profile);
    fieldsLayout->addRow(friendList);
    fieldsLayout->addRow(leaderBoard);
    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 125, this->size().height() / 2 -40);

    this->show();
}

void MainGUI::displayGameModesMenu() {

    QDialogButtonBox* dialog = new QDialogButtonBox;
    dialog->setWindowTitle("Select a game mode");

    dialog->addButton("CLASSIC MODE", QDialogButtonBox::AcceptRole);
    dialog->addButton("TEAM MODE",  QDialogButtonBox::AcceptRole);
    dialog->addButton("TIMED MODE",  QDialogButtonBox::AcceptRole);

    //TODO: connecter les boutons et gg

    dialog->move(this->width() /2, this->height()/2);
    dialog->show();
    /*
    delete newGame;
    delete spectator;
    delete profile;
    delete friendList;
    delete leaderBoard;
    delete exit;

    QFrame * fields = new QFrame(this);
    QFormLayout * fieldsLayout = new QFormLayout(this);

    QString s1 = "CLASSIC MODE";
    QString s2 = "TIMED MODE";
    QString s3 = "TEAM MODE";
    QString s4 = "CANCEL";

    classicMode = new QCustomButton(1, s1,fields);
    classicMode->setFixedSize(QSize(212,45));

    timedMode = new QCustomButton(2, s2,fields);
    timedMode->setFixedSize(QSize(212,45));

    teamMode = new QCustomButton(3, s3,fields);
    teamMode->setFixedSize(QSize(212,45));

    cancel = new QCustomButton(4, s4,fields);
    cancel->setFixedSize(QSize(212,45));

    QObject::connect(classicMode, SIGNAL(clicked(int)), this, SLOT(handleGameModeChoice(int)));
    QObject::connect(timedMode, SIGNAL(clicked(int)), this, SLOT(handleGameModeChoice(int)));
    QObject::connect(teamMode, SIGNAL(clicked(int)), this, SLOT(handleGameModeChoice(int)));
    QObject::connect(cancel, SIGNAL(clicked(int)), this, SLOT(handleGameModeChoice(int)));

    fieldsLayout->addRow(classicMode);
    fieldsLayout->addRow(timedMode);
    fieldsLayout->addRow(teamMode);
    fieldsLayout->addRow(cancel);
    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 125, this->size().height() / 2 +105);

    this->showMaximized();
    // créer un slot qui fera appel à handleGameModeChoice
    */

}

void MainGUI::handleMenuChoice(int choice) {
    std::cout << choice << std::endl;
    menuChoice = choice;
    manager->handleUserMenuChoice();
}

void MainGUI::handleGameModeChoice(int choice){
    // TODO: gameModeChoice = le choix de l'utilisateur;
    std::cout << choice << std::endl;
    gameModeChoice = choice;
    manager->handleGameModeChoice();
}