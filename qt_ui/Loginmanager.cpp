#include "Loginmanager.h"

LoginManager::LoginManager() : QWidget(nullptr){

    QFile File("/Users/Jurgen/qtinfo209/americanLogin.qss");
    File.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(File.readAll());
    this->setStyleSheet(styleSheet);

    //---------------------------------------------------------------------------------
    this->setFixedHeight(600);
    this->setFixedWidth(750);
    QPixmap bkgnd("/Users/Jurgen/Desktop/game pictures/backgrounds/americanBg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    //---------------------------------------------------------------------------------
    QFont police("calibri");

    QFrame * fields = new QFrame(this);
    QFormLayout * fieldsLayout = new QFormLayout;

    QLineEdit * userLine_ = new QLineEdit( fields);
    userLine_->setSelection(0, 10);
    usernameL = userLine_;

    QLineEdit * passLine_ = new QLineEdit( fields);
    passLine_->setEchoMode(QLineEdit::Password); // Display bullets instead of char
    passwordL = passLine_;

    QString s1 = "USERNAME  ";
    QString s2 = "PASSWORD  ";
    QString s3 = "LOGIN";

    QLabel *l1 = new QLabel();
    l1->setText(s1);
    l1-> setFont(police);

    QLabel *l2 = new QLabel();
    l2->setText(s2);
    l2-> setFont(police);

    QPushButton *connectButton = new QPushButton("LOGIN",fields);
    connectButton->setFixedSize(QSize(212,45));
    QObject::connect(connectButton, SIGNAL(clicked()), this, SLOT(loginUser()));

    fieldsLayout->addRow(l1, userLine_);
    fieldsLayout->addRow(l2, passLine_);
    fieldsLayout->addRow(connectButton);
    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 125, this->size().height() / 2 +105);

    QMediaPlayer *player = new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("/Users/Jurgen/Desktop/game pictures/sounds/americanAnthem.mp3"));
    player->setVolume(100);
    player->play();

}

void LoginManager::loginUser(){
    QString username = usernameL->text();
    QString password = passwordL->text();

    // send login request

}
