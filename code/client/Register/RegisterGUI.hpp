//
// Created by jepsiko on 09/03/17.
//

#ifndef PROJET_REGISTERGUI_HPP
#define PROJET_REGISTERGUI_HPP


#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include "../Abstract/AbstractGUI.hpp"

class RegisterManager;

class RegisterGUI : public AbstractGUI {
Q_OBJECT

public slots:
    void registerUser();

private:
    RegisterManager *manager;
    QLineEdit *usernameL;
    QLineEdit *passwordL;
    QLineEdit *confirmL;
    QPushButton *connect;
    std::string username;
    std::string password;

public:
    RegisterGUI(RegisterManager *manager);
    void setupGUI();
    std::string getUsername();
    std::string getPassword();
};


#endif //PROJET_REGISTERGUI_HPP
