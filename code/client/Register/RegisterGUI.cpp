#include <QtCore/QFile>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtMultimedia/QMediaPlayer>
#include <QtWidgets/QMessageBox>
#include "RegisterGUI.hpp"
#include "RegisterManager.hpp"

RegisterGUI::RegisterGUI(RegisterManager *manager) : manager(manager) {}

void RegisterGUI::display() {
    setStylesheetFromPath("../../qt_ui/americanLogin.qss");

    this->setFixedHeight(600);
    this->setFixedWidth(750);

    setBackgroundFromPath("../../qt_ui/game_pictures/backgrounds/americanBg");

    QFont police("calibri");

    QFrame * fields = new QFrame(this);
    QFormLayout * fieldsLayout = new QFormLayout;

    usernameL = new QLineEdit(fields);
    usernameL->setSelection(0, 10);

    passwordL = new QLineEdit(fields);
    passwordL->setEchoMode(QLineEdit::Password); // Display bullets instead of char

    confirmL = new QLineEdit(fields);
    confirmL->setEchoMode(QLineEdit::Password); // Display bullets instead of char

    QString s1 = "USERNAME";
    QString s2 = "PASSWORD";
    QString s3 = "CONFIRM";
    QString s4 = "REGISTER";
    QString s5 = "CANCEL";

    QLabel *l1 = new QLabel();
    l1->setText(s1);
    l1->setFont(police);

    QLabel *l2 = new QLabel();
    l2->setText(s2);
    l2->setFont(police);

    QLabel *l3 = new QLabel();
    l3->setText(s3);
    l3->setFont(police);

    connect = new QPushButton(s4,fields);
    connect->setFixedSize(QSize(212,45));
    connect->setCursor(Qt::PointingHandCursor);


    cancel = new QPushButton(s5,fields);
    cancel->setFixedSize(QSize(212,45));
    cancel->setCursor(Qt::PointingHandCursor);


    QObject::connect(usernameL, SIGNAL(returnPressed()), passwordL, SLOT(setFocus()));
    QObject::connect(passwordL, SIGNAL(returnPressed()), confirmL, SLOT(setFocus()));
    QObject::connect(confirmL, SIGNAL(returnPressed()), connect, SIGNAL(clicked()));
    QObject::connect(connect, SIGNAL(clicked()), this, SLOT(registerUser()));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cancelRegister()));

    fieldsLayout->addRow(l1, usernameL);
    fieldsLayout->addRow(l2, passwordL);
    fieldsLayout->addRow(l3, confirmL);
    fieldsLayout->addRow(connect);
    fieldsLayout->addRow(cancel);
    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 125, this->size().height() / 2 +105);

    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("../../qt_ui/game_pictures/sounds/americanAnthem.mp3"));
    player->setVolume(100);
    player->play();

    this->show();
}

void RegisterGUI::registerUser() {
    username = usernameL->text().toStdString();
    password = passwordL->text().toStdString();
    confirm = confirmL->text().toStdString();

    manager->registerUser();
}

void RegisterGUI::displaySuccess() {
    QMessageBox::information(this, "Registered successfully", "Your account was registered successfully, you can now login normally.");
    passwordL->setText("");
    confirmL->setText("");
}

void RegisterGUI::displayError() {
    QMessageBox::critical(this, "Error in register", "Error : This username is already used or is not valid");
    passwordL->setText("");
    confirmL->setText("");
}

void RegisterGUI::displayConfirmError() {
    QMessageBox::critical(this, "Confirmation error", "ERROR : Your password doesn't correspond to the confirmation");
    passwordL->setText("");
    confirmL->setText("");
}

void RegisterGUI::cancelRegister() {
    manager->goToWelcome();
}
