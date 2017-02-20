//
//

#ifndef PROJET_ABSTRACTMANAGER_H
#define PROJET_ABSTRACTMANAGER_H


class AbstractManager {

    AbstractManager manager;


public:
    virtual void run() = 0;
    virtual ~AbstractManager() = default;

};


#endif //PROJET_ABSTRACTMANAGER_H
