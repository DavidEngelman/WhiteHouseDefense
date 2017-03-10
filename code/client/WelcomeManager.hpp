#ifndef PROJET_WELCOMEMANAGER_H
#define PROJET_WELCOMEMANAGER_H

#include "AbstractManager.hpp"
#include "WelcomeUI.hpp"
#include "LoginManager.hpp"
#include "RegisterManager.hpp"

class WelcomeGUI;

class WelcomeManager : public AbstractManager {

private:
    WelcomeUI welcomeUI;
    WelcomeGUI *welcomeGUI;


public:
    WelcomeManager(App* my_app);
    void run() override;
    void goToLogin();
    void goToRegister();

};


#endif //PROJET_WELCOMEMANAGER_H
