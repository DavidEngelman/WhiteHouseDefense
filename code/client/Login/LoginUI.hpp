#ifndef PROJET_LOGINUI_HPP
#define PROJET_LOGINUI_HPP

#include <string>
#include "LoginManager.hpp"

class LoginManager;

class LoginUI {
protected:
    LoginManager *manager;
public:
    LoginUI(LoginManager * manager): manager(manager) {};
    // NE PAS ENLEVER. FONDAMENTAL POUR ASSURER LA DESTRUCTION CORRECTE DES OBJETS;
    virtual ~LoginUI() = default;
    virtual std::string getUsername() = 0;
    virtual std::string getPassword() = 0;
    virtual void display() = 0;
    virtual void displayError() = 0;
    virtual void displayAlreadyConnected() = 0;
};

#endif //PROJET_LOGINUI_HPP
