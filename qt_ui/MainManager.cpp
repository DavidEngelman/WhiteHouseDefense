#include "MainManager.h"
#include "ui_MainManager.h"

MainManager::MainManager(QWidget *parent) : QWidget(parent){

    setTheme(1);

    QFrame * fields = new QFrame(this);
    QFormLayout * fieldsLayout = new QFormLayout;

    loginButton = new QPushButton("LOGIN",fields);
    loginButton->setFixedSize(QSize(212,45));
    QObject::connect(loginButton, SIGNAL(clicked()), this, SLOT(this->close()));

    registerButton = new QPushButton("REGISTER",fields);
    registerButton->setFixedSize(QSize(212,45));
    QObject::connect(registerButton, SIGNAL(clicked()), this, SLOT(openWindow(2)));

    quitButton = new QPushButton("QUIT",fields);
    quitButton->setFixedSize(QSize(212,45));
    QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(loginUser(3)));

    fieldsLayout->addRow(loginButton);
    fieldsLayout->addRow(registerButton);
    fieldsLayout->addRow(quitButton);

    fields->setLayout(fieldsLayout);
    fields->move(this->size().width() / 2 - 125, this->size().height() / 2 +100);

}
void MainManager::openWindow(int windowType){
    if (windowType == 1){
        LoginManager * login = new LoginManager();
        login->show();
    }else if (windowType == 3){
        this->close();
    }
}


void MainManager::setTheme(int themeInt){
    QFile File;
    QString styleSheet;
    QPixmap bkgnd;
    QPalette palette;
    QMediaPlayer *player = new QMediaPlayer;

    switch (themeInt) {
    case 1:
        File.setFileName("/Users/Jurgen/qtinfo209/americanMain.qss");
        File.open(QFile::ReadOnly);
        styleSheet = QLatin1String(File.readAll());
        this->setStyleSheet(styleSheet);
        this->setFixedHeight(600);
        this->setFixedWidth(750);
        bkgnd = QPixmap("/Users/Jurgen/Desktop/game pictures/backgrounds/americanBg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);
        player->setMedia(QUrl::fromLocalFile("/Users/Jurgen/Desktop/game pictures/sounds/americanAnthem.mp3"));
        player->setVolume(100);
        player->play();

        break;

    case 2:
        File.setFileName("/Users/Jurgen/qtinfo209/urssMain.qss");
        File.open(QFile::ReadOnly);
        styleSheet = QLatin1String(File.readAll());
        this->setStyleSheet(styleSheet);
        this->setFixedHeight(600);
        this->setFixedWidth(800);
        bkgnd = QPixmap("/Users/Jurgen/Desktop/game pictures/backgrounds/urssBg");
        bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        palette.setBrush(QPalette::Background, bkgnd);
        this->setPalette(palette);
        player->setMedia(QUrl::fromLocalFile("/Users/Jurgen/Desktop/game pictures/sounds/urssAnthem.mp3"));
        player->setVolume(100);
        player->play();

        break;
    default:
        break;
    }
}

MainManager::~MainManager(){

}
