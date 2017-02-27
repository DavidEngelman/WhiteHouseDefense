#ifndef PROJET_ABSTRACTMANAGER_H
#define PROJET_ABSTRACTMANAGER_H

#include "App.hpp"

class AbstractManager {

protected:

    App* master_app;
    char* server_ip_address;

public:
    AbstractManager(char* addr, App* my_app);

    virtual void run() = 0;
    virtual ~AbstractManager();

};


#endif //PROJET_ABSTRACTMANAGER_H
