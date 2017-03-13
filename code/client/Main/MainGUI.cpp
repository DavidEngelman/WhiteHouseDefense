#include "MainGUI.hpp"
#include <QtCore/QFile>
#include <QtWidgets/QFormLayout>
#include <QtMultimedia/QMediaPlayer>

MainGUI::MainGUI(MainManager *manager) : MainUI(manager) {}

void MainGUI::display() {
    QFile File("../../qt_ui/americanLogin.qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(styleSheet);

    this->setFixedHeight(600);
    this->setFixedWidth(750);
    QPixmap bkgnd("../../qt_ui/game_pictures/backgrounds/Whitehouse");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
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
