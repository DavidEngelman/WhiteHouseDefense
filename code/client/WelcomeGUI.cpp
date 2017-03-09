//
// Created by jepsiko on 09/03/17.
//

#include <iostream>
#include "WelcomeGUI.hpp"

void WelcomeGUI::setupGUI() {
    fieldsLayout = new QFormLayout;

    loginButton = new QPushButton("LOGIN", this);
    loginButton->setFixedSize(QSize(212,45));
    QObject::connect(loginButton, SIGNAL(clicked()), this, SLOT(openWindow("LOGIN")));

    registerButton = new QPushButton("REGISTER", this);
    registerButton->setFixedSize(QSize(212,45));
    QObject::connect(registerButton, SIGNAL(clicked()), this, SLOT(openWindow("REGISTER")));

    quitButton = new QPushButton("QUIT", this);
    quitButton->setFixedSize(QSize(212,45));
    QObject::connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    fieldsLayout->addRow(loginButton);
    fieldsLayout->addRow(registerButton);
    fieldsLayout->addRow(quitButton);

    this->setLayout(fieldsLayout);
    this->show();
}

void WelcomeGUI::openWindow(std::string windowType) {
    if (windowType == "LOGIN"){
        std::cout << "LOGIN" << std::endl;
    }else if (windowType == "REGISTER"){
        std::cout << "REGISTER" << std::endl;
    } else {
        std::cerr << "UNKNOWN" << std::endl;
    }
}
