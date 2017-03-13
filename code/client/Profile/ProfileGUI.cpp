#include <QtCore/QFile>
#include <QtWidgets/QFrame>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QMessageBox>
#include "ProfileGUI.hpp"

ProfileGUI::ProfileGUI(ProfileManager *manager) : ProfileUI(manager), usernameT(new QString("No Username")), victoriesT(new QString),
NPCKilledT(new QString) {}


ProfileGUI::~ProfileGUI() {
    close();
}


void ProfileGUI::display() {


    /* Set stylesheet */
    setStylesheetFromPath("../../qt_ui/profile.qss");

    /* Set dimensions */
    this->setFixedHeight(480);
    this->setFixedWidth(852);

    /* Set background */
    setBackgroundFromPath("../../qt_ui/game_pictures/backgrounds/profile_bckgrd.jpeg");

    QFont police("calibri");
    QFont policeUsername("calibri", 24, QFont::Bold);

    QVBoxLayout *maingridLayout = new QVBoxLayout(this);
    QGridLayout *searchgridlayout = new QGridLayout;


    //QFrame *frame = new QFrame(this);
    //QVBoxLayout *mainLayout = new QVBoxLayout(frame);
    //QFormLayout *fieldsLayout = new QFormLayout();

    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setSelection(0, 10);

    QString usernameString = "Username";
    QString searchButtonString = "SEARCH";

    QPixmap* victoryPic = new QPixmap("../../qt_ui/game_pictures/pictures/trophy2.png");
    QLabel *victoryPicLabel = new QLabel(this);
    victoryPicLabel->setFixedSize(victoryPic->size());
    victoryPicLabel->setPixmap(*victoryPic);

    QPixmap* mexicanPic = new QPixmap("../../qt_ui/game_pictures/pictures/mexican.gif");
    QLabel *mexicanPicLabel = new QLabel(this);
    mexicanPicLabel->setFixedSize(mexicanPic->size());
    mexicanPicLabel->setPixmap(*mexicanPic);

    QLabel *label = new QLabel(this);
    label->setText(usernameString);
    label->setFont(police);

    searchButton = new QPushButton(searchButtonString, this);
    searchButton->setFixedSize(QSize(212, 45));

    QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(showUser()));
    QObject::connect(usernameLineEdit, SIGNAL(returnPressed()), searchButton, SIGNAL(clicked()));

    searchgridlayout->addWidget(label, 0, 0);
    searchgridlayout->addWidget(usernameLineEdit, 0, 1);
    searchgridlayout->addWidget(searchButton, 0, 2);
    maingridLayout->addLayout(searchgridlayout);
    maingridLayout->setAlignment(searchgridlayout, Qt::AlignTop);


    *usernameT = QString::fromStdString(profileManager->getUsername());
    *victoriesT = QString::fromStdString("Victories:\n" + std::to_string(profileManager->getVictories()));
    *NPCKilledT = QString::fromStdString("NPC killed:\n" + std::to_string(profileManager->getNPCKilled()));

    userNameLabel = new QLabel(this);
    userNameLabel->wordWrap();
    userNameLabel->setFont(policeUsername);
    userNameLabel->setText(*usernameT);

    victoriesLabel = new QLabel(this);
    victoriesLabel->setFont(police);
    victoriesLabel->setText(*victoriesT);

    NPCKilledLabel = new QLabel(this);
    NPCKilledLabel->setFont(police);
    NPCKilledLabel->setText(*NPCKilledT);

    std::cout << (*usernameT).toStdString() << std::endl;
    std::cout << (*victoriesT).toStdString() << std::endl;
    std::cout << (*NPCKilledT).toStdString() << std::endl;

    userNameLabel->move((this->width()/2) - usernameT->size()/2, this->height()/2 - 105 );
    victoryPicLabel->move(this->width()/2 - 124, this->height()/2 + 22);
    victoriesLabel->move(this->width()/2  - 100, this->height()/2 + 135 );
    NPCKilledLabel->move(this->width()/2  + 100, this->height()/2 + 135 );
    mexicanPicLabel->move(this->width()/2 + 95, this->height()/2 + 5);

    this->setLayout(maingridLayout);

    this->show();
}

void ProfileGUI::displayNoSuchProfileError() {
    QMessageBox::critical(this, "No such profile", "Error : There is no profile with that username");
}

void ProfileGUI::updateProfile() {
    *usernameT = QString::fromStdString(profileManager->getUsername());
    *victoriesT = QString::fromStdString("Victories: " + std::to_string(profileManager->getVictories()));
    *NPCKilledT = QString::fromStdString("NPC killed: " + std::to_string(profileManager->getNPCKilled()));

    userNameLabel->setText(*usernameT);
    victoriesLabel->setText(*victoriesT);
    NPCKilledLabel->setText(*NPCKilledT);

//    this
}

void ProfileGUI::showUser() {
    username = usernameLineEdit->text().toStdString();
    profileManager->showProfile();
}
