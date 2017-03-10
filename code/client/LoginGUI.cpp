//
// Created by jepsiko on 09/03/17.
//

#include <QtCore/QFile>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtMultimedia/QMediaPlayer>
#include <QtWidgets/QMessageBox>
#include "LoginGUI.hpp"
#include "LoginManager.hpp"

void LoginGUI::loginUser() {
    username = usernameL->text().toStdString();
    password = passwordL->text().toStdString();

    manager->login();
}

void LoginGUI::setupGUI() {
    QFile File("../../qt_ui/americanLogin.qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(styleSheet);

    this->setFixedHeight(600);
    this->setFixedWidth(750);
    QPixmap bkgnd("../../qt_ui/game_pictures/backgrounds/americanBg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    QFont police("calibri");

    QFrame * fields = new QFrame(this);
    QFormLayout * fieldsLayout = new QFormLayout;

    usernameL = new QLineEdit(fields);
    usernameL->setSelection(0, 10);

    passwordL = new QLineEdit(fields);
    passwordL->setEchoMode(QLineEdit::Password); // Display bullets instead of char

    QString s1 = "USERNAME  ";
    QString s2 = "PASSWORD  ";
    QString s3 = "LOGIN";

    QLabel *l1 = new QLabel();
    l1->setText(s1);
    l1->setFont(police);

    QLabel *l2 = new QLabel();
    l2->setText(s2);
    l2->setFont(police);

    connect = new QPushButton("LOGIN",fields);
    connect->setFixedSize(QSize(212,45));
    QObject::connect(connect, SIGNAL(clicked()), this, SLOT(loginUser()));

    fieldsLayout->addRow(l1, usernameL);
    fieldsLayout->addRow(l2, passwordL);
    fieldsLayout->addRow(connect);
    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 125, this->size().height() / 2 +105);

    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("../../qt_ui/game_pictures/sounds/americanAnthem.mp3"));
    player->setVolume(100);
    player->play();

    this->show();
}

std::string LoginGUI::getUsername() {
    return username;
}

std::string LoginGUI::getPassword() {
    return password;
}

void LoginGUI::displayError() {
    QMessageBox::critical(this, "Error in login", "Error : username or password incorrect, please try again");
    passwordL->setText("");
}

void LoginGUI::displayAlreadyConnected() {
    QMessageBox::critical(this, "Already connected", "Error : Someone is already connected on this account");
    passwordL->setText("");
}

LoginGUI::LoginGUI(LoginManager *manager) : manager(manager){}
