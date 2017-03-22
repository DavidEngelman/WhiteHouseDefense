#include "MainGUI.hpp"
#include <QtCore/QFile>
#include <QtWidgets/QFormLayout>
#include <QtMultimedia/QMediaPlayer>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>


MainGUI::MainGUI(MainManager *manager, QWidget* _parent) : AbstractGUI(_parent), MainUI(manager) {}

void MainGUI::display() {


    this->setFixedHeight(600);
    this->setFixedWidth(1000);

    setStylesheetFromPath("../../qt_ui/americanMain.qss");
    setBackgroundFromPath("../../qt_ui/game_pictures/backgrounds/whitehouse_bckgrd.png");
    manager->setMusicFromPath("../../qt_ui/game_pictures/sounds/trump_song.mp3");

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

    settings = new QCustomButton(6, "SETTINGS", fields);
    settings->setFixedSize(QSize(212,45));

    QObject::connect(newGame, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(spectator, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(profile, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(friendList, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(leaderBoard, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));
    QObject::connect(settings, SIGNAL(clicked(int)), this, SLOT(handleMenuChoice(int)));


    fieldsLayout->addRow(newGame);
    fieldsLayout->addRow(spectator);
    fieldsLayout->addRow(profile);
    fieldsLayout->addRow(friendList);
    fieldsLayout->addRow(leaderBoard);
    fieldsLayout->addRow(settings);

    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 125, this->size().height() / 2 -60);

    if (manager->isInQueue()){
        showInQueue();
    }

    this->show();
    AbstractGUI::parent->setVisible(true);

}

void MainGUI::displayGameModesMenu() {

    dialog_game_mode_choice = new QWidget;
    dialog_game_mode_choice->setWindowTitle("Select a game mode");
    dialog_game_mode_choice->setWindowModality(Qt::ApplicationModal);

    popup_h_layout = new QHBoxLayout;
    dialog_game_mode_choice->setLayout(popup_h_layout);

    classicMode = new QCustomButton(0, "CLASSIC MODE", dialog_game_mode_choice);
    teamMode = new QCustomButton(1, "TEAM MODE", dialog_game_mode_choice);
    timedMode = new QCustomButton(2, "TIMED MODE", dialog_game_mode_choice);

    popup_h_layout->addWidget(classicMode);
    popup_h_layout->addWidget(teamMode);
    popup_h_layout->addWidget(timedMode);

    connect(classicMode, SIGNAL(clicked(int)), this, SLOT(handleGameModeChoice(int)));
    connect(teamMode, SIGNAL(clicked(int)), this, SLOT(handleGameModeChoice(int)));
    connect(timedMode, SIGNAL(clicked(int)), this, SLOT(handleGameModeChoice(int)));

    dialog_game_mode_choice->move(this->width() /2, this->height()/2);
    dialog_game_mode_choice->show();

}

void MainGUI::handleMenuChoice(int choice) {
    menuChoice = choice;
    manager->handleUserMenuChoice();
}

void MainGUI::handleGameModeChoice(int choice){
    showInQueue();
    dialog_game_mode_choice->close();
    dialog_game_mode_choice->deleteLater();
    gameModeChoice = choice;
    manager->handleGameModeChoice();


}

void MainGUI::showInQueue(){
    newGame->setEnabled(false);
    queueWidget = new InQueueWidget(this);
    queueWidget->move(this->width()-200, this->height()-70);

}

void MainGUI::leaveQueue(){
    newGame->setEnabled(true);
    queueWidget->hide();
    queueWidget->deleteLater();

    manager->leaveQueue();

}