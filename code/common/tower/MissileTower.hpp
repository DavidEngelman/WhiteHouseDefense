

#ifndef PROJET_MISSILETOWER_HPP
#define PROJET_MISSILETOWER_HPP


#include "AttackTower.hpp"

class MissileTower : public AttackTower {
public:
    MissileTower(const Position &position, int level);

    ~MissileTower() = default;

    virtual const std::vector<PNJ *> shoot(Wave &wave, PlayerState& playerState) override;

    virtual std::string serialize() override;

    std::vector<PNJ*> get_targets(Wave& wave, PNJ* closestTarget);

    std::string getType() override;

    PNJ *get_closest_pnj(Wave &wave);

    void dealDamageToSubTargets(PNJ &target, PlayerState &playerState);
};


#endif //PROJET_MISSILETOWER_HPP
