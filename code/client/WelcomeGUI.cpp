//
// Created by jepsiko on 09/03/17.
//

#include <iostream>
#include <QtWidgets/QFrame>
#include <QCoreApplication>
#include "WelcomeGUI.hpp"

WelcomeGUI::WelcomeGUI(QWidget *parent) : QWidget(parent){}


void WelcomeGUI::setupGUI() {
    QFrame * fields = new QFrame(this);
    fieldsLayout = new QFormLayout;

    loginButton = new QPushButton("LOGIN", fields);
    loginButton->setFixedSize(QSize(212,45));
    connect(loginButton, SIGNAL (released()), this, SLOT (openWindow()));

    registerButton = new QPushButton("REGISTER", fields);
    registerButton->setFixedSize(QSize(212,45));
    connect(registerButton, SIGNAL (released()), this, SLOT (openWindow()));

    quitButton = new QPushButton("QUIT", fields);
    quitButton->setFixedSize(QSize(212,45));
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));

    fieldsLayout->addRow(loginButton);
    fieldsLayout->addRow(registerButton);
    fieldsLayout->addRow(quitButton);

    this->setLayout(fieldsLayout);
    this->show();
}

void WelcomeGUI::openWindow() {
    std::cout << "opening window" << std::endl;
}

WelcomeGUI::~WelcomeGUI(){

}