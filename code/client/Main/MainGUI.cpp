#include "MainGUI.hpp"
#include <QtCore/QFile>
#include <QtWidgets/QFormLayout>
#include <QtMultimedia/QMediaPlayer>
#include <QtWidgets/QDialogButtonBox>


MainGUI::MainGUI(MainManager *manager) : MainUI(manager) {}

void MainGUI::display() {

    this->setFixedHeight(600);
    this->setFixedWidth(1000);

    setStylesheetFromPath("../../qt_ui/americanLogin.qss");
    setBackgroundFromPath("../../qt_ui/game_pictures/backgrounds/whitehouse_bckgrd.png");
    setMusicFromPath("../../qt_ui/game_pictures/sounds/trump_song.mp3");

    QFont police("calibri");

    QFrame * fields = new QFrame(this);
    QFormLayout * fieldsLayout = new QFormLayout(this);

    newGame = new QCustomButton(1, "NEW GAME", fields);
    newGame->setFixedSize(QSize(212,45));

    spectator = new QCustomButton(2, "SPECTATOR", fields);
    spectator->setFixedSize(QSize(212,45));

    profile = new QCustomButton(3, "PROFILE", fields);
    profile->setFixedSize(QSize(212,45));

    friendList = new QCustomButton(4, "FRIEND LIST", fields);
    friendList->setFixedSize(QSize(212,45));

    leaderBoard = new QCustomButton(5, "LEADERBOARD", fields);
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

    classicMode = new QCustomButton(0, "CLASSIC MODE", dialog);
    teamMode = new QCustomButton(1, "TEAM MODE", dialog);
    timedMode = new QCustomButton(2, "TEAM MODE", dialog);
    cancel = new QCustomButton(3, "CANCEL", dialog);

    dialog->addButton(cancel, QDialogButtonBox::DestructiveRole);
    dialog->addButton(timedMode,  QDialogButtonBox::AcceptRole);
    dialog->addButton(teamMode,  QDialogButtonBox::AcceptRole);
    dialog->addButton(classicMode, QDialogButtonBox::AcceptRole);

    connect(classicMode, SIGNAL(clicked(int)), this, SLOT(handleGameModeChoice(int)));
    connect(teamMode, SIGNAL(clicked(int)), this, SLOT(handleGameModeChoice(int)));
    connect(timedMode, SIGNAL(clicked(int)), this, SLOT(handleGameModeChoice(int)));
    connect(cancel, SIGNAL(clicked(int)), this, SLOT(handleGameModeChoice(int)));


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