#ifndef PROJET_ATTACKTOWER_H
#define PROJET_ATTACKTOWER_H


#include "AbstractTower.hpp"
#include "../pnj/PNJ.hpp"
#include "../Constants.hpp"

class AttackTower : public AbstractTower {
    int damage;

public:

    AttackTower(Position position, int damage, int price, float range, int level);

    ~AttackTower() = default;

    int getDamageAmount() const;

    virtual void dealDamageTo(PNJ &pnj);
};

#endif //PROJET_ATTACKTOWER_H
