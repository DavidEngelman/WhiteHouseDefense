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

    QFrame *frame = new QFrame(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(frame);
    QFormLayout *fieldsLayout = new QFormLayout();

    usernameLineEdit = new QLineEdit(frame);
    usernameLineEdit->setSelection(0, 10);

    QString usernameString = "Username";
    QString searchButtonString = "SEARCH";

    QLabel *label = new QLabel(frame);
    label->setText(usernameString);
    label->setFont(police);

    searchButton = new QPushButton(searchButtonString, frame);
    searchButton->setFixedSize(QSize(212, 45));

    QObject::connect(searchButton, SIGNAL(clicked()), this, SLOT(showUser()));
    QObject::connect(usernameLineEdit, SIGNAL(returnPressed()), searchButton, SIGNAL(clicked()));

    fieldsLayout->addRow(label, usernameLineEdit);
    fieldsLayout->addRow(searchButton);

    *usernameT = QString::fromStdString("Username: " + profileManager->getUsername());
    *victoriesT = QString::fromStdString("Victories: " + std::to_string(profileManager->getVictories()));
    *NPCKilledT = QString::fromStdString("NPC killed: " + std::to_string(profileManager->getNPCKilled()));

    userNameLabel = new QLabel(frame);
    userNameLabel->setFont(police);
    userNameLabel->setText(*usernameT);

    victoriesLabel = new QLabel(frame);
    victoriesLabel->setFont(police);
    victoriesLabel->setText(*victoriesT);

    NPCKilledLabel = new QLabel(frame);
    NPCKilledLabel->setFont(police);
    NPCKilledLabel->setText(*NPCKilledT);

    std::cout << (*usernameT).toStdString() << std::endl;
    std::cout << (*victoriesT).toStdString() << std::endl;
    std::cout << (*NPCKilledT).toStdString() << std::endl;

    mainLayout->addLayout(fieldsLayout);
    mainLayout->addWidget(userNameLabel);
    mainLayout->addWidget(victoriesLabel);
    mainLayout->addWidget(NPCKilledLabel);

    frame->setLayout(mainLayout);
    frame->move(this->size().width() / 2 - 125, this->size().height() / 2 - 105);

    this->show();
}

void ProfileGUI::displayNoSuchProfileError() {
    QMessageBox::critical(this, "No such profile", "Error : There is no profile with that username");
}

void ProfileGUI::updateProfile() {
    *usernameT = QString::fromStdString("Username: " + profileManager->getUsername());
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
