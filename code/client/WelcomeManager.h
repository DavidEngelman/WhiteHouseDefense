//
//

#ifndef PROJET_WELCOMEMANAGER_H
#define PROJET_WELCOMEMANAGER_H

#include "AbstractManager.h"
#include "WelcomeUI.h"
#include "LoginManager.hpp"
#include "RegisterManager.hpp"

class WelcomeManager : public AbstractManager {

private:
    WelcomeUI welcomeUI;


public:
    WelcomeManager(char* ip_addr);
    void welcome_process();
    void run() override;

};


#endif //PROJET_WELCOMEMANAGER_H
