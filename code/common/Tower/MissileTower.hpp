

#ifndef PROJET_MISSILETOWER_HPP
#define PROJET_MISSILETOWER_HPP


#include "AttackTower.hpp"
#include "OneTargetTower.hpp"

class MissileTower : public virtual AttackTower, public virtual OneTargetTower {
public:
    MissileTower(const Position &position, int level);

    ~MissileTower() = default;

    virtual const std::vector<PNJ *> shoot(Wave &wave, PlayerState& playerState) override;

    virtual std::string serialize() override;

    std::vector<PNJ*> get_targets(Wave& wave, PNJ* closestTarget);

    std::string getType() override;

    void dealDamageToSubTargets(PNJ &target, PlayerState &playerState);
};


#endif //PROJET_MISSILETOWER_HPP
