#include "MainManager.h"
#include <QCoreApplication>

MainManager::MainManager(QWidget *parent) : QWidget(parent){

    setTheme(1);

    QFrame * fields = new QFrame(this);
    QFormLayout * fieldsLayout = new QFormLayout;

    loginButton = new QPushButton("LOGIN",fields);
    loginButton->setFixedSize(QSize(212,45));
    connect(loginButton, SIGNAL (released()), this, SLOT (openWindow()));

    registerButton = new QPushButton("REGISTER",fields);
    registerButton->setFixedSize(QSize(212,45));
    connect(registerButton, SIGNAL (released()), this, SLOT (openWindow()));

    quitButton = new QPushButton("QUIT",fields);
    quitButton->setFixedSize(QSize(212,45));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    fieldsLayout->addRow(loginButton);
    fieldsLayout->addRow(registerButton);
    fieldsLayout->addRow(quitButton);

    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 125, this->size().height() / 2 +100);

}
void MainManager::openWindow(){

    LoginManager * login = new LoginManager();
    this->hide();
    login->show();

}


void MainManager::setTheme(int themeInt){
    QFile File;
    QString styleSheet;
    QPixmap bkgnd;
    QPalette palette;
    QMediaPlayer *player = new QMediaPlayer;

    switch (themeInt) {
    case 1:
        File.setFileName("../qt_ui/americanMain.qss");
        File.open(QFile::ReadOnly);
        styleSheet = QLatin1String(File.readAll());
        this->setStyleSheet(styleSheet);
        this->setFixedHeight(600);
        this->setFixedWidth(750);
        bkgnd = QPixmap("../qt_ui/game_pictures/backgrounds/americanBg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);
        player->setMedia(QUrl::fromLocalFile("../qt_ui/game_pictures/sounds/americanAnthem.mp3"));
        player->setVolume(100);
        player->play();

        break;

    case 2:
        File.setFileName("../qt_ui/urssMain.qss");
        File.open(QFile::ReadOnly);
        styleSheet = QLatin1String(File.readAll());
        this->setStyleSheet(styleSheet);
        this->setFixedHeight(600);
        this->setFixedWidth(800);
        bkgnd = QPixmap("../qt_ui/game_pictures/backgrounds/urssBg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);
        player->setMedia(QUrl::fromLocalFile("../qt_ui/game_pictures/sounds/urssAnthem.mp3"));
        player->setVolume(100);
        player->play();

        break;
    default:
        break;
    }
}

MainManager::~MainManager(){

}
