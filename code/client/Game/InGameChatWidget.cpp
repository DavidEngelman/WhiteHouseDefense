#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include "InGameChatWidget.hpp"

InGameChatWidget::InGameChatWidget(GameManager *gameManager) : gameManager(gameManager) {
    QFont police("calibri");

    QVBoxLayout *mainLayout = new QVBoxLayout();

    /* Message list view */
    messagesListWidget = new QListWidget();
    messagesListWidget->addItem("Je suis bob l'eponge");
    messagesListWidget->addItem("J'aime les patates");


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
}

void InGameChatWidget::addChatMessage(const std::string &message, const std::string &sender) {
    std::string totalMessage = sender + ": " + message;
    // TODO: il y a une segmentation fault quand cette ligne n'est pas commentée :(
//    messagesListWidget->addItem(totalMessage.c_str());
}


