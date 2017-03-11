#include <QtCore/QFile>
#include <QtWidgets/QFrame>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include "ProfileGUI.hpp"

ProfileGUI::ProfileGUI(ProfileManager *manager) : ProfileUI(manager) {}


void ProfileGUI::display() {
    // TODO
    std::string infos = manager->getProfile(manager->getUsername());
    std::cout << infos << std::endl;

    QLabel *name = new QLabel;


    this->show();
}

void ProfileGUI::displayNoSuchProfileError() {
    // TODO
}

void ProfileGUI::displayProfile(std::string profileData) {
    // TODO
}
