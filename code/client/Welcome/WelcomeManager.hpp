#ifndef PROJET_WELCOMEMANAGER_H
#define PROJET_WELCOMEMANAGER_H

#include "../Abstract/AbstractManager.hpp"
#include "WelcomeUI.hpp"
#include "../Login/LoginManager.hpp"
#include "../Register/RegisterManager.hpp"

class WelcomeGUI;

class WelcomeManager : public AbstractManager {

private:
    WelcomeUI welcomeUI;
    WelcomeGUI *welcomeGUI;


public:
    WelcomeManager(App* my_app);
    ~WelcomeManager();
    void run() override;
    void goToLogin();
    void goToRegister();

};


#endif //PROJET_WELCOMEMANAGER_H
