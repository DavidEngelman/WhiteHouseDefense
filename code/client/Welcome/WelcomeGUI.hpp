//
// Created by jepsiko on 09/03/17.
//

#ifndef PROJET_WELCOMEGUI_HPP
#define PROJET_WELCOMEGUI_HPP


#include <QMainWindow>
#include <QLineEdit>
#include <QMessageBox>
#include <QLabel>
#include <QFile>
#include <QPushButton>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QFrame>
#include <QtMultimedia/QMediaPlayer>
#include <QGraphicsEffect>
#include "../Abstract/AbstractGUI.hpp"

class WelcomeManager;

class WelcomeGUI : public AbstractGUI {

    Q_OBJECT

private:
    WelcomeManager *manager;
    QPushButton *loginButton;
    QPushButton *registerButton;
    QPushButton *quitButton;
    QFormLayout *fieldsLayout;
    void setTheme();

public slots:
    void openLogin();
    void openRegister();

public:
    WelcomeGUI(WelcomeManager *manager);
    virtual ~WelcomeGUI();

    void setupGUI();
};


#endif //PROJET_WELCOMEGUI_HPP
