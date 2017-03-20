#ifndef PROJET_GUNTOWER_H
#define PROJET_GUNTOWER_H

#include "AttackTower.hpp"
#include "../pnj/PNJ.hpp"
#include "../Constants.hpp"

class GunTower : public AttackTower {

public:

    GunTower(const Position &position, int level);

    ~GunTower() = default;

    virtual const std::vector<PNJ *> shoot(Wave &wave, PlayerState& playerState) override;

    virtual std::string serialize() override;
    
    PNJ* get_closest_pnj(Wave& wave);

    std::string getType() override;
};


#endif //PROJET_GUNTOWER_H
