//
//

#ifndef PROJET_APP_HPP
#define PROJET_APP_HPP


#include "AbstractManager.h"

class AbstractManager;

class App {

private:

    AbstractManager current_mamanger;

public:

    App(char* server_ip_addr);

    virtual void transition(AbstractManager new_manager);

    virtual ~App() = default;

};


#endif //PROJET_APP_HPP
