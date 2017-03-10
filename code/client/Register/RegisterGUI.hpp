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
    void cancelRegister();

private:
    RegisterManager *manager;
    QLineEdit *usernameL;
    QLineEdit *passwordL;
    QLineEdit *confirmL;
    QPushButton *connect;
    QPushButton *cancel;
    std::string username;
    std::string password;
    std::string confirm;

public:
    RegisterGUI(RegisterManager *manager);
    void setupGUI();

    std::string getUsername() { return username; };
    std::string getPassword() { return password; };
    std::string getConfirm() { return confirm; };

    void displaySuccess();
    void displayError();
    void displayConfirmError();
};


#endif //PROJET_REGISTERGUI_HPP
