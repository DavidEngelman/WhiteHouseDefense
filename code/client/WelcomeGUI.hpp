//
// Created by jepsiko on 09/03/17.
//

#ifndef PROJET_WELCOMEGUI_HPP
#define PROJET_WELCOMEGUI_HPP


#include <QtWidgets/QPushButton>
#include <QtWidgets/QFormLayout>
#include "AbstractGUI.hpp"

class WelcomeGUI : public AbstractGUI {
    Q_OBJECT

private:
    QPushButton *loginButton;
    QPushButton *registerButton;
    QPushButton *quitButton;
    QFormLayout *fieldsLayout;

public slots:
    void openWindow(std::string windowType);

public:
    void setupGUI();
};


#endif //PROJET_WELCOMEGUI_HPP
