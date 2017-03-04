#ifndef PROJET_GUNTOWER_H
#define PROJET_GUNTOWER_H

#include "AttackTower.hpp"
#include "PNJ.hpp"
#include "../common/Constants.h"

class GunTower : public AttackTower {

public:

    GunTower(const Position &position);

    ~GunTower() = default;

    virtual bool shoot(Wave &wave) override;

    virtual std::string serialize() override;
    
    PNJ* get_closest_pnj(Wave& wave);
};


#endif //PROJET_GUNTOWER_H
