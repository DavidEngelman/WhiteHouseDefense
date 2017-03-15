#include "MainGUI.hpp"
#include <QtCore/QFile>
#include <QtWidgets/QFormLayout>
#include <QtMultimedia/QMediaPlayer>

MainGUI::MainGUI(MainManager *manager) : MainUI(manager) {}

void MainGUI::display() {
    setStylesheetFromPath("../../qt_ui/americanLogin.qss");

    this->setFixedHeight(600);
    this->setFixedWidth(750);
    this->showFullScreen();

    QScreen *screen = QGuiApplication::primaryScreen();//?????

    QPalette palette;
    palette.setColor(QPalette::Background,QColor::fromRgb(0,0,80));//faut trouver la bonne couleur
    this->setPalette(palette);
    QFont police("calibri");
    this->show();

    // TODO: créer un slot qui appele handleUserMenuChoice() du manager;
}

void MainGUI::displayGameModesMenu() {
    // TODO: lui proposer le choix
    // créer un slot qui fera appel à handleGameModeChoice
}

void MainGUI::handleMenuChoice() {
    // TODO: menuChoice = le choix de l'utilisateur
    manager->handleUserMenuChoice();
}

void MainGUI::handleGameModeChoice(){
    // TODO: gameModeChoice = le choix de l'utilisateur;
    manager->handleGameModeChoice();
}
