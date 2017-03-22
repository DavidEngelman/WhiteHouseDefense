

#ifndef PROJET_ONETARGETTOWER_HPP
#define PROJET_ONETARGETTOWER_HPP


#include "AbstractTower.hpp"

class OneTargetTower : public virtual AbstractTower {
public:
    OneTargetTower(const Position &position, int price, float range, int level);

    PNJ *getClosestPNJ(Wave &wave);
};


#endif //PROJET_ONETARGETTOWER_HPP
