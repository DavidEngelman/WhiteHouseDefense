#ifndef PROJET_ATTACKTOWER_H
#define PROJET_ATTACKTOWER_H


#include "AbstractTower.hpp"
#include "PNJ.hpp"

// TODO: mettre des vraies valeurs
const int ATTACK_TOWER_PRICE = 10;
const int ATTACK_TOWER_RANGE = 10;
const int ATTACK_TOWER_DAMAGE = 10;

class AttackTower : public AbstractTower {

private:

    int damageAmount;

public:

    AttackTower(Position position);

    virtual ~AttackTower() = default;

    virtual int getDamageAmount() const;

    virtual void setDamageAmount(int newDamageAmount);

    virtual bool shoot(Wave &wave) override;

    virtual void dealDamageTo(PNJ &pnj);

    virtual std::string serialize() override;

};

#endif //PROJET_ATTACKTOWER_H
