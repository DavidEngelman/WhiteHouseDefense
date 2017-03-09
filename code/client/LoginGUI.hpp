//
// Created by jepsiko on 09/03/17.
//

#ifndef PROJET_LOGINGUI_HPP
#define PROJET_LOGINGUI_HPP


#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "AbstractGUI.hpp"

class LoginGUI : public AbstractGUI {
    Q_OBJECT

public slots:
    void loginUser();

private:
    QLineEdit *usernameL;
    QLineEdit *passwordL;
    QPushButton *connect;

public:
    void setupGUI();
};


#endif //PROJET_LOGINGUI_HPP
