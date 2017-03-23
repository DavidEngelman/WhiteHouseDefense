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
#include "WelcomeUI.hpp"

class WelcomeGUI : public AbstractGUI, public WelcomeUI {

Q_OBJECT

private:
    QPushButton *loginButton;
    QPushButton *registerButton;
    QPushButton *quitButton;
    QFormLayout *fieldsLayout;

    void setTheme();

public slots:

    void openLogin();

    void openRegister();

public:
    WelcomeGUI(WelcomeManager *manager, QWidget *_parent);

    virtual ~WelcomeGUI();

    void display() override;
};


#endif //PROJET_WELCOMEGUI_HPP
