//
// Created by jepsiko on 09/03/17.
//

#ifndef PROJET_LOGINGUI_HPP
#define PROJET_LOGINGUI_HPP


#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "../Abstract/AbstractGUI.hpp"
#include "LoginConsoleUI.hpp"

class LoginManager;

class LoginGUI : public AbstractGUI, public LoginUI {
    Q_OBJECT

public slots:
    void loginUser();

private:
    QLineEdit *usernameL;
    QLineEdit *passwordL;
    QPushButton *connect;
    std::string username;
    std::string password;

public:
    LoginGUI(LoginManager *manager);
    virtual ~LoginGUI();


    std::string getUsername() { return username; };
    std::string getPassword() { return password; };
    void display();
    void displayError();
    void displayAlreadyConnected();
};


#endif //PROJET_LOGINGUI_HPP
