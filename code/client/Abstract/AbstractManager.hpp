#ifndef PROJET_ABSTRACTMANAGER_H
#define PROJET_ABSTRACTMANAGER_H

#include "../App.hpp"
#include "../global.hpp"

class MainManager;

class AbstractManager {

protected:

    App* master_app;

public:
    AbstractManager(App* my_app) : master_app(my_app) {};
    virtual ~AbstractManager() = default;

    virtual void run() = 0;

    void setMusicFromPath(QString path);
};


#endif //PROJET_ABSTRACTMANAGER_H
