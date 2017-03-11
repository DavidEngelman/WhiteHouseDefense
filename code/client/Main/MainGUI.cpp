//
// Created by jepsiko on 09/03/17.
//

#include "MainGUI.hpp"
#include "MainManager.hpp"
#include <QtCore/QFile>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtMultimedia/QMediaPlayer>
#include <QtWidgets/QMessageBox>

MainGUI::MainGUI(MainManager *manager) : manager(manager) {}

void MainGUI::setupGUI() {
    QFile File("../../qt_ui/americanLogin.qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(styleSheet);

    this->setFixedHeight(600);
    this->setFixedWidth(750);
    this->showFullScreen();

    QScreen *screen = QGuiApplication::primaryScreen();//?????

    QPalette palette;
    palette.setColor(QPalette::Background,QColor::fromRgb(0,0,80));//faut trouver la bonne couleur
    this->setPalette(palette);
    QFont police("calibri");
    this->show();
}