#include "MainManager.h"
#include <QCoreApplication>

MainManager::MainManager(QWidget *parent) : QWidget(parent){

    this->setFixedHeight(480);
    this->setFixedWidth(852);

    QPixmap bkgnd("../qt_ui/game_pictures/backgrounds/profile_bckgrd.jpeg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    QFont policeUsername("calibri", 24, QFont::Bold);
    QFont policeStandart("calibri", 12, QFont::Bold);


    ///----------LAYOUTS----------

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *searchLayout = new QHBoxLayout;
    QHBoxLayout *statsLayout = new QHBoxLayout;
    QVBoxLayout *victoryLayout = new QVBoxLayout;
    QVBoxLayout *NPCLayout = new QVBoxLayout;


    ///----------SEARCH----------

    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText("SEARCH PROFILE...");
    //usernameLineEdit->setText("SEARCH PROFILE...");
    usernameLineEdit->setFixedWidth(300);
    usernameLineEdit->setFixedHeight(35);

    QString usernameString = "Username";
    QString searchButtonString = "SEARCH";

    searchButton = new QPushButton(searchButtonString, this);
    searchButton->setFixedSize(QSize(111, 35));

    searchLayout->addWidget(usernameLineEdit);
    searchLayout->addWidget(searchButton);

    ///----------USERNAME----------

    usernameT = new QString;

    *usernameT = QString::fromStdString("Benjamin"); //profileManager->getUsername()

    userNameLabel = new QLabel(this);
    userNameLabel->setText(*usernameT);
    userNameLabel->setFont(policeUsername);
    userNameLabel->setStyleSheet("padding-top: 100;color : gold;");

    ///----------VICTORIES----------

    victoriesT = new QString;
    *victoriesT = QString::fromStdString("Victories: 10 "); //"Victories:\n" + std::to_string(profileManager->getVictories())

    victoriesLabel = new QLabel(this);
    victoriesLabel->setFont(policeStandart);
    victoriesLabel->setText(*victoriesT);
    victoriesLabel->setStyleSheet("padding-left: 200;color : gold;");

    QPixmap* victoryPic = new QPixmap("../qt_ui/game_pictures/pictures/trophy2.png");
    QLabel *victoryPicLabel = new QLabel(this);
    victoryPicLabel->setFixedWidth(400);
    victoryPicLabel->setPixmap(*victoryPic);
    victoryPicLabel->setStyleSheet("padding-left: 230;");


    victoryLayout->addWidget(victoriesLabel);
    victoryLayout->addWidget(victoryPicLabel);
    victoryLayout->setAlignment(victoriesLabel, Qt::AlignCenter|Qt::AlignBottom);
    victoryLayout->setAlignment(victoryPicLabel, Qt::AlignCenter|Qt::AlignTop);

    ///----------NPC KILLED----------

    NPCKilledT = new QString;
    *NPCKilledT = QString::fromStdString("NPC killed: 40"); //"NPC killed:\n" + std::to_string(profileManager->getNPCKilled())


    NPCKilledLabel = new QLabel(this);
    NPCKilledLabel->setFont(policeStandart);
    NPCKilledLabel->setText(*NPCKilledT);
    NPCKilledLabel->setStyleSheet("padding-right: 200;color : gold;");


    QPixmap* mexicanPic = new QPixmap("../qt_ui/game_pictures/pictures/mexican.gif");
    QLabel *mexicanPicLabel = new QLabel(this);
    mexicanPicLabel->setFixedWidth(400);
    mexicanPicLabel->setPixmap(*mexicanPic);
    mexicanPicLabel->setStyleSheet("padding-left: 40;");


    NPCLayout->addWidget(NPCKilledLabel);
    NPCLayout->addWidget(mexicanPicLabel);
    NPCLayout->setAlignment(NPCKilledLabel, Qt::AlignCenter|Qt::AlignBottom);
    NPCLayout->setAlignment(mexicanPicLabel, Qt::AlignCenter|Qt::AlignTop);

    ///----------SETUP----------

    statsLayout->addLayout(victoryLayout);
    statsLayout->addLayout(NPCLayout);
    statsLayout->setAlignment(victoryLayout, Qt::AlignLeft|Qt::AlignBottom);
    statsLayout->setAlignment(NPCLayout, Qt::AlignRight|Qt::AlignBottom);


    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(userNameLabel);
    mainLayout->addLayout(statsLayout);


    mainLayout->setAlignment(searchLayout, Qt::AlignRight|Qt::AlignTop);
    mainLayout->setAlignment(userNameLabel, Qt::AlignHCenter|Qt::AlignTop);

    mainLayout->setStretch(1,1);

    this->setLayout(mainLayout);

///////////////////////////////////////////////////////////////////////////
}


MainManager::~MainManager(){

}
