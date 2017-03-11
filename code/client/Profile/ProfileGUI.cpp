#include <QtCore/QFile>
#include <QtWidgets/QFrame>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMessageBox>
#include "ProfileGUI.hpp"

ProfileGUI::ProfileGUI(ProfileManager *manager) : ProfileUI(manager) {}

ProfileGUI::~ProfileGUI() {
    close();
}


void ProfileGUI::display() {
    // TODO
//    std::string infos = manager->getAndParseProfile(manager->getPlayerUsername());
//    std::cout << infos << std::endl;

    QLabel *name = new QLabel;


    this->show();
}

void ProfileGUI::displayNoSuchProfileError() {
    QMessageBox::critical(this, "No such profile", "Error : There is no profile with that username");
}

void ProfileGUI::displayProfile() {
    // TODO
}
