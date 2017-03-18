#ifndef PROJET_IN_GAME_CHAT_WIDGET_HPP
#define PROJET_IN_GAME_CHAT_WIDGET_HPP


#include <QtWidgets/QWidget>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include "../QHandPointerButton.hpp"
#include "GameManager.hpp"

class InGameChatWidget: public QWidget {
    Q_OBJECT

private:
    GameManager * gameManager;
    QListWidget * messagesListWidget;
    QLineEdit * messageLineEdit;
    QHandPointerButton * sendButton;

public slots:
    void sendMessage();

public:
    InGameChatWidget(GameManager * gameManager);
    virtual ~InGameChatWidget() = default;

    void addChatMessage(const std::string &message, const std::string &sender);
};


#endif //PROJET_IN_GAME_CHAT_WIDGET_HPP
