#ifndef PROJET_APP_HPP
#define PROJET_APP_HPP

#include "WelcomeManager.h"

class AbstractManager;

class App {

private:

    AbstractManager* current_manager;

public:

    //App() = default;

    App(char* server_ip_addr);

    virtual void init(char* addr);
    virtual void transition(AbstractManager *new_manager);

    ~App() = default;

};


#endif //PROJET_APP_HPP
