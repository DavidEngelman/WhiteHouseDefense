#ifndef PROJET_ABSTRACTMANAGER_H
#define PROJET_ABSTRACTMANAGER_H

#include "App.hpp"

class AbstractManager {


public:

    virtual void run() = 0;
    virtual ~AbstractManager() = default;

};


#endif //PROJET_ABSTRACTMANAGER_H
