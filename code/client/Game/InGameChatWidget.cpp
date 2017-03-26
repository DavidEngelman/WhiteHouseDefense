#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include "InGameChatWidget.hpp"
#include "../Other/QCustomButton.hpp"

InGameChatWidget::InGameChatWidget(GameManager *gameManager) : gameManager(gameManager) {
    QFont police("calibri");

    QVBoxLayout *mainLayout = new QVBoxLayout();

    /* Message list view */
    messagesListWidget = new QListWidget();


    /* Send message form */
    QHBoxLayout *fieldsLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    messageLineEdit = new QLineEdit;
    sendButton = new QHandPointerButton("SEND", 150, 25);

    QObject::connect(messageLineEdit, SIGNAL(returnPressed()), sendButton, SIGNAL(clicked()));
    QObject::connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));

    fieldsLayout->addWidget(messageLineEdit);
    fieldsLayout->addWidget(sendButton);

    QHBoxLayout *buttonsLayout = new QHBoxLayout();
    QCustomButton *button1 = new QCustomButton(0, QString::fromStdString(MESSAGES[0]));
    QCustomButton *button2 = new QCustomButton(1, QString::fromStdString(MESSAGES[1]));
    QCustomButton *button3 = new QCustomButton(2, QString::fromStdString(MESSAGES[2]));

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
    gameManager->sendMessageToPlayers(MESSAGES[choice]);
}

void InGameChatWidget::addChatMessage(const std::string &message, const std::string &sender) {
    std::string totalMessage = sender + ": " + message;

    QListWidgetItem *item = new QListWidgetItem(totalMessage.c_str());
    if (sender == gameManager->getUsername()) item->setForeground(Qt::darkGreen);
    if (message == MESSAGES[1]) playSound("../../qt_ui/game_pictures/sounds/america_great_again.mp3");

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


