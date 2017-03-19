#ifndef PROJET_ATTACKTOWER_H
#define PROJET_ATTACKTOWER_H


#include "AbstractTower.hpp"
#include "PNJ.hpp"
#include "../common/Constants.h"

class AttackTower : public AbstractTower {
    int damage;

public:

    AttackTower(Position position, int damage, int price, float range, int level);

    ~AttackTower() = default;

    int getDamageAmount() const;

    virtual void dealDamageTo(PNJ &pnj);
};

#endif //PROJET_ATTACKTOWER_H
