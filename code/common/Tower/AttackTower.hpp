#ifndef PROJET_ATTACKTOWER_H
#define PROJET_ATTACKTOWER_H


#include "AbstractTower.hpp"
#include "../Npc/PNJ.hpp"
#include "../Other/Constants.hpp"

class AttackTower : public virtual AbstractTower {
    int damage;

public:

    AttackTower(Position position, int damage, int price, float range, int level);
    AttackTower(int damage);

    ~AttackTower() = default;

    int getDamageAmount() const;

    virtual void dealDamageTo(PNJ &pnj, PlayerState& playerState);
};

#endif //PROJET_ATTACKTOWER_H
