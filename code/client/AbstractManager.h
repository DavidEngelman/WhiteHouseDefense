#ifndef PROJET_ABSTRACTMANAGER_H
#define PROJET_ABSTRACTMANAGER_H

class App;

class AbstractManager {

protected:

    App* my_master_app;

public:

    virtual void run() = 0;
    virtual ~AbstractManager() = default;

};


#endif //PROJET_ABSTRACTMANAGER_H
