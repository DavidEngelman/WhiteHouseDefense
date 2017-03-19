#include "SettingsGUI.hpp"

SettingsGUI::SettingsGUI(SettingsManager *manager, QWidget* _parent) : AbstractGUI(_parent), SettingsUI(manager) {}

void SettingsGUI::display() {

    this->setFixedHeight(600);
    this->setFixedWidth(1000);

    /* Set background */
    setBackgroundFromPath("../../qt_ui/game_pictures/backgrounds/profile_bckgrd-2.png");




}

std::string SettingsGUI::getNewUsername() {
    return std::__cxx11::string();
}

std::string SettingsGUI::getNewPassword() {
    return std::__cxx11::string();
}

std::string SettingsGUI::getNewIconName() {
    return std::__cxx11::string();
}
