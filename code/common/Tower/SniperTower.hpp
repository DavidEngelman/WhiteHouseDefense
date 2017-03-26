#ifndef PROJET_SNIPERTOWER_HPP
#define PROJET_SNIPERTOWER_HPP


#include "AttackTower.hpp"
#include "OneTargetTower.hpp"

class SniperTower : public AttackTower, public OneTargetTower {

public:
    SniperTower(const Position &position, int level);

    virtual ~SniperTower() = default;

    virtual const std::vector<PNJ *> shoot(Wave &wave, PlayerState& playerState) override;

    virtual std::string serialize() override;

    std::string getType() override;
};


#endif //PROJET_SNIPERTOWER_HPP
