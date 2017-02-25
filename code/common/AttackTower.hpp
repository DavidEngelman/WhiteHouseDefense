#ifndef PROJET_ATTACKTOWER_H
#define PROJET_ATTACKTOWER_H


#include "AbstractTower.hpp"
#include "PNJ.hpp"

class AttackTower : public AbstractTower {

private:

    int damageAmount;

public:

    AttackTower(Position position, int price, int radius, int damageAmount);

    virtual ~AttackTower() = default;

    virtual int getDamageAmount() const;

    virtual void setDamageAmount(int newDamageAmount);

    virtual bool shoot(Wave& wave) override;







    virtual void dealDamageTo(PNJ& pnj);

    virtual std::string serialize() override;

};

#endif //PROJET_ATTACKTOWER_H
