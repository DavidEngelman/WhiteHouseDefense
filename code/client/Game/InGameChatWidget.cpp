#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include "InGameChatWidget.hpp"
#include "../Other/QCustomButton.hpp"

InGameChatWidget::InGameChatWidget(GameManager *gameManager) : gameManager(gameManager) {
    QFont police("calibri");
    QVBoxLayout *mainLayout = new QVBoxLayout();

    /* Message list view */
    messagesListWidget = new QListWidget();
    messagesListWidget->setFixedWidth(250);
    messagesListWidget->setStyleSheet("border-image:url(../../qt_ui/resources/backgrounds/goldBg.png);color : black;border-radius : 5px;;border-width : 2px;border-style :solid ;border-color: gold ;");


    /* Send message form */
    QHBoxLayout *fieldsLayout = new QHBoxLayout();

    messageLineEdit = new QLineEdit;
    messageLineEdit->setStyleSheet("QLineEdit,QLineEdit:hover{border-radius : 10px;border-style :solid ;border-color: gold ;border-width: 2px;background-image: url(../../qt_ui/resources/backgrounds/goldBg.png);color :black;}");
    messageLineEdit->setFixedSize(200,30);
    sendButton = new QHandPointerButton("SEND", 50, 25);
    sendButton->setStyleSheet("QPushButton{ border-image:url(../../qt_ui/resources/buttons/mainmenu.png);color :black;} QPushButton:pressed{ border-image:url(../../qt_ui/resources/buttons/connectPressed.png);color :black;}");

    QObject::connect(messageLineEdit, SIGNAL(returnPressed()), sendButton, SIGNAL(clicked()));
    QObject::connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));

    fieldsLayout->addWidget(messageLineEdit);
    fieldsLayout->addWidget(sendButton);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    QCustomButton *button1 = new QCustomButton(0, QString::fromStdString(MESSAGES_BUTTONS[0]));
    button1->setFont(QFont("calibri", 7));
    button1->setFixedSize(75,30);
    button1->setStyleSheet("QPushButton{ border-image:url(../../qt_ui/resources/buttons/mainmenu.png);color :black;} QPushButton:pressed{ border-image:url(../../qt_ui/resources/buttons/connectPressed.png);color :black;}");
    QCustomButton *button2 = new QCustomButton(1, QString::fromStdString(MESSAGES_BUTTONS[1]));
    button2->setFixedSize(75,30);
    button2->setFont(QFont("calibri", 7));
    button2->setStyleSheet("QPushButton{ border-image:url(../../qt_ui/resources/buttons/mainmenu.png);color :black;} QPushButton:pressed{ border-image:url(../../qt_ui/resources/buttons/connectPressed.png);color :black;}");

    QCustomButton *button3 = new QCustomButton(2, QString::fromStdString(MESSAGES_BUTTONS[2]));
    button3->setFont(QFont("calibri", 7));
    button3->setFixedSize(75,30);

    button3->setStyleSheet("QPushButton{ border-image:url(../../qt_ui/resources/buttons/mainmenu.png);color :black;} QPushButton:pressed{ border-image:url(../../qt_ui/resources/buttons/connectPressed.png);color :black;}");

    connect(button1, SIGNAL(clicked(int)), this, SLOT(handleMessageChoice(int)));
    connect(button2, SIGNAL(clicked(int)), this, SLOT(handleMessageChoice(int)));
    connect(button3, SIGNAL(clicked(int)), this, SLOT(handleMessageChoice(int)));

    buttonsLayout->addWidget(button1);
    buttonsLayout->addWidget(button2);
    buttonsLayout->addWidget(button3);

    /* Bringing it all together */
    mainLayout->addWidget(messagesListWidget);
    mainLayout->addLayout(fieldsLayout);
    mainLayout->addLayout(buttonsLayout);
    this->setLayout(mainLayout);
}

void InGameChatWidget::sendMessage() {
    std::string message = messageLineEdit->text().toStdString();
    gameManager->sendMessageToPlayers(message);
    messageLineEdit->setText("");
}

void InGameChatWidget::handleMessageChoice(int choice) {
    gameManager->sendMessageToPlayers(MESSAGES_CONTENT[choice]);
}

void InGameChatWidget::addChatMessage(const std::string &message, const std::string &sender) {
    std::string totalMessage = sender + ": " + message;

    QListWidgetItem *item = new QListWidgetItem(totalMessage.c_str());
    if (sender == gameManager->getUsername()) item->setForeground(Qt::darkGreen);
    else if (sender.find("[SERVER]") != std::string::npos) item->setForeground(Qt::darkRed);
    else if (sender.find("[TEAM]") != std::string::npos) item->setForeground(Qt::darkMagenta);
    else if (sender.find("[PRIVATE]") != std::string::npos) item->setForeground(Qt::darkBlue);

    if (message == MESSAGES_CONTENT[1]) {
        playSound("../../qt_ui/resources/sounds/america_great_again.mp3");
    }

    messagesListWidget->addItem(item);
}

void InGameChatWidget::playSound(QString musicPath) {

    QMediaPlayer *mediaPlayer = new QMediaPlayer;
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile(QFileInfo(musicPath).absoluteFilePath()));

    mediaPlayer->setVolume(100);
    mediaPlayer->setPlaylist(playlist);
    mediaPlayer->play();
}


