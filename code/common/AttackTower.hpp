#ifndef PROJET_ATTACKTOWER_H
#define PROJET_ATTACKTOWER_H


#include "AbstractTower.hpp"
#include "PNJ.hpp"

class AttackTower : public AbstractTower {

private:

    int damageAmount;

public:

    virtual int getDamageAmount() const;

    virtual void setDamageAmount(int damageAmount);

    virtual void shoot(PNJ target);

    virtual void dealDamageTo(PNJ pnj);

    virtual std::string serialize() override;

};


#endif //PROJET_ATTACKTOWER_H
