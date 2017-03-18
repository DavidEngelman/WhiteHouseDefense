#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include "InGameChatWidget.hpp"

InGameChatWidget::InGameChatWidget(GameManager *gameManager) : gameManager(gameManager) {
    QFont police("calibri");

    QVBoxLayout *mainLayout = new QVBoxLayout();

    /* Message list view */
    messagesListWidget = new QListWidget();


    /* Send message form */
    QHBoxLayout *fieldsLayout = new QHBoxLayout();

    messageLineEdit = new QLineEdit;
    sendButton = new QHandPointerButton("SEND", 150, 25);

    QObject::connect(messageLineEdit, SIGNAL(returnPressed()), sendButton, SIGNAL(clicked()));
    QObject::connect(sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));

    fieldsLayout->addWidget(messageLineEdit);
    fieldsLayout->addWidget(sendButton);

    /* Bringing it all together */
    mainLayout->addWidget(messagesListWidget);
    mainLayout->addLayout(fieldsLayout);
    this->setLayout(mainLayout);
}

void InGameChatWidget::sendMessage() {
    std::string message = messageLineEdit->text().toStdString();
    gameManager->sendMessageToPlayers(message);
    messageLineEdit->setText("");
}

void InGameChatWidget::addChatMessage(const std::string &message, const std::string &sender) {
    std::string totalMessage = sender + ": " + message;

    QListWidgetItem *item = new QListWidgetItem(totalMessage.c_str());
    if (sender == gameManager->getUsername()) item->setForeground(Qt::darkGreen);
    messagesListWidget->addItem(item);
}


