#include <QtCore/QFile>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtMultimedia/QMediaPlayer>
#include <QtWidgets/QMessageBox>
#include <QtCore/QFileInfo>
#include "LoginGUI.hpp"

void LoginGUI::loginUser() {
    username = usernameL->text().toStdString();
    password = passwordL->text().toStdString();

    manager->login();
}

void LoginGUI::display() {
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
    QFormLayout * fieldsLayout = new QFormLayout(this);

    usernameL = new QLineEdit(fields);
    usernameL->setSelection(0, 10);

    passwordL = new QLineEdit(fields);
    passwordL->setEchoMode(QLineEdit::Password); // Display bullets instead of char

    QString s1 = "USERNAME";
    QString s2 = "PASSWORD";
    QString s3 = "LOGIN";
    QString s4 = "CANCEL";

    QLabel *l1 = new QLabel(fields);
    l1->setText(s1);
    l1->setFont(police);

    QLabel *l2 = new QLabel(fields);
    l2->setText(s2);
    l2->setFont(police);

    connect = new QPushButton(s3,fields);
    connect->setFixedSize(QSize(212,45));
    connect->setCursor(Qt::PointingHandCursor);


    cancel = new QPushButton(s4,fields);
    cancel->setFixedSize(QSize(212,45));
    cancel->setCursor(Qt::PointingHandCursor);


    QObject::connect(connect, SIGNAL(clicked()), this, SLOT(loginUser()));
    QObject::connect(usernameL, SIGNAL(returnPressed()), passwordL, SLOT(setFocus()));
    QObject::connect(passwordL, SIGNAL(returnPressed()), connect, SIGNAL(clicked()));
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(cancelLogin()));

    fieldsLayout->addRow(l1, usernameL);
    fieldsLayout->addRow(l2, passwordL);
    fieldsLayout->addRow(connect);
    fieldsLayout->addRow(cancel);
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

LoginGUI::LoginGUI(LoginManager *manager) : LoginUI(manager){}

LoginGUI::~LoginGUI() {
    std::cout << "Login GUI closed." << std::endl;
    disconnect(connect, 0, 0, 0);
    disconnect(usernameL, 0, 0, 0);
    disconnect(passwordL, 0, 0, 0);
    disconnect(cancel, 0, 0, 0);

    //close();
}

void LoginGUI::cancelLogin() {
    manager->goToWelcome();
}
