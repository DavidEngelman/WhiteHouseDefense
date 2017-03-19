#include <QtCore/QFile>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtMultimedia/QMediaPlayer>
#include <QtWidgets/QMessageBox>
#include <QtCore/QFileInfo>
#include "LoginGUI.hpp"
#include "../QHandPointerButton.hpp"

void LoginGUI::loginUser() {
    username = usernameL->text().toStdString();
    password = passwordL->text().toStdString();

    manager->login();
}

void LoginGUI::display() {
    setStylesheetFromPath("../../qt_ui/americanLogin.qss");

    this->setFixedHeight(600);
    this->setFixedWidth(750);

    setBackgroundFromPath("../../qt_ui/game_pictures/backgrounds/americanBg");

    QFont police("calibri");

    QFrame * fields = new QFrame(this);
    QFormLayout * fieldsLayout = new QFormLayout(fields);

    usernameL = new QLineEdit(fields);
    usernameL->setSelection(0, 10);

    passwordL = new QLineEdit(fields);
    passwordL->setEchoMode(QLineEdit::Password); // Display bullets instead of char

    QLabel *usernameLabel = new QLabel(fields);
    usernameLabel->setText("USERNAME");
    usernameLabel->setFont(police);

    QLabel *passwordLabel = new QLabel(fields);
    passwordLabel->setText("PASSWORD");
    passwordLabel->setFont(police);

    connect = new QHandPointerButton("LOGIN", 212, 45, fields);
    cancel = new QHandPointerButton("CANCEL", 212, 45, fields);


    QObject::connect(usernameL, SIGNAL(returnPressed()), passwordL, SLOT(setFocus()));
    QObject::connect(passwordL, SIGNAL(returnPressed()), connect, SIGNAL(clicked()));
    QObject::connect(connect, SIGNAL(clicked()), this, SLOT(loginUser()));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cancelLogin()));

    fieldsLayout->addRow(usernameLabel, usernameL);
    fieldsLayout->addRow(passwordLabel, passwordL);
    fieldsLayout->addRow(connect);
    fieldsLayout->addRow(cancel);
    fieldsLayout->setAlignment(connect, Qt::AlignCenter);
    fieldsLayout->setAlignment(cancel, Qt::AlignCenter);
    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 125, this->size().height() / 2 +105);

    QMediaPlayer *player = new QMediaPlayer(this);
    // Les path relatifs marchen en utilisant QFileInfo
    player->setMedia(QUrl::fromLocalFile(QFileInfo("../../qt_ui/game_pictures/sounds/americanAnthem.mp3").absoluteFilePath()));
    player->setVolume(100);
    player->play();

    this->show();
}

void LoginGUI::displayError() {
    QMessageBox::critical(this, "Error in login", "Error : username or password incorrect, please try again");
    passwordL->setText("");
}

void LoginGUI::displayAlreadyConnected() {
    QMessageBox::critical(this, "Already connected", "Error : Someone is already connected on this account");
    passwordL->setText("");
}

LoginGUI::LoginGUI(LoginManager *manager, QWidget* _parent) : AbstractGUI(_parent), LoginUI(manager){}

LoginGUI::~LoginGUI() {}

void LoginGUI::cancelLogin() {
    manager->goToWelcome();
}

//void LoginGUI::destroy() {
//    AbstractGUI::destroy();
//}
