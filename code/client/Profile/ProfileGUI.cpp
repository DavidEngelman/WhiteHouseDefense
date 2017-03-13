//
// Created by jepsiko on 09/03/17.
//

#include <QtCore/QFile>
#include <QtWidgets/QFrame>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QLabel>
#include "ProfileGUI.hpp"

ProfileGUI::ProfileGUI(ProfileManager *manager) : manager(manager) {}


void ProfileGUI::display() {
    std::string infos = manager->getProfile(manager->getUsername());
    std::cout <<infos << std::endl;

    QLabel *name = new QLabel;



    this->show();
}
