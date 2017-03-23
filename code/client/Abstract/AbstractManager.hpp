#ifndef PROJET_ABSTRACTMANAGER_H
#define PROJET_ABSTRACTMANAGER_H

#include "../Other/App.hpp"
#include "../Other/global.hpp"

class MainManager;

class AbstractManager {

protected:

    App* master_app;

public:
    AbstractManager(App* my_app) : master_app(my_app) {};
    virtual ~AbstractManager() = default;

    virtual void run() = 0;

    void setMusicFromPath(QString path);

    void centerWindow();
    
    App* getMasterApp();
};


#endif //PROJET_ABSTRACTMANAGER_H
