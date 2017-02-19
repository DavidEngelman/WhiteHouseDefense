#ifndef PROJET_ATTACKTOWER_H
#define PROJET_ATTACKTOWER_H


#include "AbstractTower.hpp"

class AttackTower : public AbstractTower {

private:

    int damageAmount;

public:

    virtual int getDamageAmount() const;

    virtual void setDamageAmount(int damageAmount);

    virtual void shoot(PNJ target);

    virtual void dealDamageTo(PNJ pnj);

};


#endif //PROJET_ATTACKTOWER_H
