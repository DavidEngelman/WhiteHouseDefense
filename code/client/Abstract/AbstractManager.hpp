#ifndef PROJET_ABSTRACTMANAGER_H
#define PROJET_ABSTRACTMANAGER_H

#include "../App.hpp"
#include "../global.hpp"

class AbstractManager {

protected:

    App* master_app;

public:
    AbstractManager(App* my_app);

    virtual void run() = 0;
    virtual ~AbstractManager();

};


#endif //PROJET_ABSTRACTMANAGER_H
