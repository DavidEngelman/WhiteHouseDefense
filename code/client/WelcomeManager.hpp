#ifndef PROJET_WELCOMEMANAGER_H
#define PROJET_WELCOMEMANAGER_H

#include "AbstractManager.hpp"
#include "WelcomeUI.hpp"
#include "LoginManager.hpp"
#include "RegisterManager.hpp"
#include "WelcomeGUI.hpp"

class WelcomeManager : public AbstractManager {

private:
    WelcomeUI welcomeUI;
    WelcomeGUI welcomeGUI;


public:
    WelcomeManager(App* my_app);
    void run() override;

};


#endif //PROJET_WELCOMEMANAGER_H
