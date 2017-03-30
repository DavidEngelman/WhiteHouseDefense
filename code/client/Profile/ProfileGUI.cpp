#include <QtCore/QFile>
#include <QtWidgets/QFrame>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QMessageBox>
#include "ProfileGUI.hpp"
#include "../Other/QHandPointerButton.hpp"

ProfileGUI::ProfileGUI(ProfileManager *manager, QWidget* _parent) : AbstractGUI(_parent), ProfileUI(manager),
                                                                    usernameT(new QString("No Username")), victoriesT(new QString),
NPCKilledT(new QString) {}


ProfileGUI::~ProfileGUI() {
    close();
}


void ProfileGUI::display() {

    this->setFixedHeight(600);
    this->setFixedWidth(1000);

    /* Set background */
    setBackgroundFromPath("../../qt_ui/resources/backgrounds/profile_bckgrd-2.png");

    QFont policeUsername("calibri", 24, QFont::Bold);
    QFont policeStandart("calibri", 12, QFont::Bold);


    ///----------LAYOUTS----------

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *topLayout = new QHBoxLayout;
    QHBoxLayout *statsLayout = new QHBoxLayout;
    QVBoxLayout *victoryLayout = new QVBoxLayout;
    QVBoxLayout *NPCLayout = new QVBoxLayout;
    QHBoxLayout *userLayout = new QHBoxLayout;

    ///----------HOME_BUTTON----------

    homeButton = new QHandPointerButton("HOME", 70, 35, this);
    homeButton->setStyleSheet("QPushButton{ border-image: url(../../qt_ui/resources/buttons/mainmenu.png) ;} QPushButton:pressed{border-image:url(../../qt_ui/resources/buttons/connectPressed.png);}");
    QObject::connect(homeButton, SIGNAL(clicked()), this, SLOT(goToMain()));


    topLayout->addWidget(homeButton);
    topLayout->setAlignment(homeButton, Qt::AlignLeft|Qt::AlignTop);

    ///----------SEARCH----------

    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText("SEARCH PROFILE...");
    usernameLineEdit->setFixedWidth(300);
    usernameLineEdit->setFixedHeight(35);
    usernameLineEdit->setStyleSheet("QLineEdit,QLineEdit:hover{border-radius : 10px;border-style :solid ;border-color: gold ;border-width: 2px;background-image: url(../../qt_ui/resources/backgrounds/goldBg.png);}");

    QString usernameString = "Username";
    QString searchButtonString = "SEARCH";

    searchButton = new QHandPointerButton(searchButtonString, 130, 35, this);
    searchButton->setStyleSheet("QPushButton{ border-image:url(../../qt_ui/resources/buttons/mainmenu.png);} QPushButton:pressed{border-image:url(../../qt_ui/resources/buttons/connectPressed.png);}");

    QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(showUser()));
    QObject::connect(usernameLineEdit, SIGNAL(returnPressed()), searchButton, SIGNAL(clicked()));

    topLayout->addWidget(usernameLineEdit);
    topLayout->addWidget(searchButton);

    //topLayout->setAlignment(usernameLineEdit, Qt::AlignHCenter);
    //topLayout->setAlignment(searchButton, Qt::AlignLeft);


    ///----------USERNAME----------

    QLabel *dummy = new QLabel(this);
    dummy->setText("                      ");
    dummy->setStyleSheet("padding-top:85;");


    usernameT = new QString;
    iconT = new QString;

    *usernameT = QString::fromStdString("Benjamin"); //profileManager->getUsername()

    userNameLabel = new QLabel(this);
    userNameLabel->setText(*usernameT);
    userNameLabel->setFont(policeUsername);
    userNameLabel->setStyleSheet("padding-top:85;padding-left:30; color : gold;");

    iconLabel = new QLabel(this);
    iconLabel->setPixmap(QPixmap(*iconT));
    iconLabel->setStyleSheet("padding-top:85; color : gold;");

    //userLayout->setSpacing(100);

    userLayout->addStretch();
    userLayout->addWidget(dummy);
    userLayout->addStretch();
    userLayout->addWidget(userNameLabel);
    userLayout->addStretch();
    userLayout->addWidget(iconLabel);
    userLayout->addStretch();

    userLayout->setAlignment(userNameLabel, Qt::AlignLeft);
    userLayout->setAlignment(userNameLabel, Qt::AlignHCenter);
    userLayout->setAlignment(iconLabel, Qt::AlignRight);


    ///----------VICTORIES----------

    victoriesT = new QString;
    *victoriesT = QString::fromStdString("Victories: 10 "); //"Victories:\n" + std::to_string(profileManager->getVictories())

    victoriesLabel = new QLabel(this);
    victoriesLabel->setFont(policeStandart);
    victoriesLabel->setText(*victoriesT);
    victoriesLabel->setStyleSheet("padding-left: 0;color : gold;");

    QPixmap* victoryPic = new QPixmap("../../qt_ui/resources/pictures/trophy2.png");
    QLabel *victoryPicLabel = new QLabel(this);
    victoryPicLabel->setFixedWidth(400);
    victoryPicLabel->setPixmap(*victoryPic);
    victoryPicLabel->setStyleSheet("padding-left: 130;");


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
    NPCKilledLabel->setStyleSheet("padding-right: 0;color : gold;");


    QPixmap* mexicanPic = new QPixmap("../../qt_ui/resources/pictures/mexican.gif");
    QLabel *mexicanPicLabel = new QLabel(this);
    mexicanPicLabel->setFixedWidth(400);
    mexicanPicLabel->setPixmap(*mexicanPic);
    mexicanPicLabel->setStyleSheet("padding-left: 140;");


    NPCLayout->addWidget(NPCKilledLabel);
    NPCLayout->addWidget(mexicanPicLabel);
    NPCLayout->setAlignment(NPCKilledLabel, Qt::AlignCenter|Qt::AlignBottom);
    NPCLayout->setAlignment(mexicanPicLabel, Qt::AlignCenter|Qt::AlignTop);

    ///----------SETUP----------

    statsLayout->addLayout(victoryLayout);
    statsLayout->addLayout(NPCLayout);
    statsLayout->setAlignment(victoryLayout, Qt::AlignLeft|Qt::AlignBottom);
    statsLayout->setAlignment(NPCLayout, Qt::AlignRight|Qt::AlignBottom);

    mainLayout->setSpacing(10);

    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(userLayout);
    mainLayout->addLayout(statsLayout);


    mainLayout->setAlignment(topLayout, Qt::AlignTop);
    mainLayout->setAlignment(userLayout, Qt::AlignTop|Qt::AlignHCenter);

    mainLayout->setStretch(1,1);
    this->setLayout(mainLayout);
    this->show();
}

void ProfileGUI::displayNoSuchProfileError() {
    QMessageBox::critical(this, "No such profile", "Error : There is no profile with that username");
}

void ProfileGUI::updateProfile() {
    *usernameT = QString::fromStdString(profileManager->getUsername());
    *victoriesT = QString::fromStdString("Victories: " + std::to_string(profileManager->getVictories()));
    *NPCKilledT = QString::fromStdString("NPC killed: " + std::to_string(profileManager->getNPCKilled()));
    *iconT =  QString::fromStdString("../../qt_ui/resources/icons/" + std::to_string(profileManager->getIconID()) + ".jpg");


    userNameLabel->setText(*usernameT);
    victoriesLabel->setText(*victoriesT);
    NPCKilledLabel->setText(*NPCKilledT);
    iconLabel->setPixmap(QPixmap(*iconT));
}

void ProfileGUI::showUser() {
    username = usernameLineEdit->text().toStdString();
    profileManager->showProfile();
}

void ProfileGUI::goToMain() {
    profileManager->goToMainMenu();

}
