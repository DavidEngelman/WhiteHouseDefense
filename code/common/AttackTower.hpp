#ifndef PROJET_ATTACKTOWER_H
#define PROJET_ATTACKTOWER_H


#include "AbstractTower.hpp"
#include "PNJ.hpp"

// TODO: mettre des vraies valeurs
// Je pense que ces différentes valeurs devraient être des attributs qui ne sont pas constants
// vu qu'on devra pouvoir faire des updates des tours et donc augmenter ou diminuer ces valeurs
const int ATTACK_TOWER_PRICE = 10;
const int ATTACK_TOWER_RANGE = 4;
const int ATTACK_TOWER_DAMAGE = 20;

class AttackTower : public AbstractTower {

public:

    AttackTower(Position position);

    ~AttackTower() = default;

    int getDamageAmount() const;

    virtual bool shoot(Wave &wave) override;

    virtual void dealDamageTo(PNJ &pnj);

    virtual std::string serialize() override;

};

#endif //PROJET_ATTACKTOWER_H
