#ifndef PROJET_SNIPERTOWER_HPP
#define PROJET_SNIPERTOWER_HPP


#include "AttackTower.hpp"
#include "OneTargetTower.hpp"

class SniperTower : public virtual AttackTower, public virtual OneTargetTower {

public:
    SniperTower(const Position &position, int level);

    ~SniperTower() = default;

    virtual const std::vector<PNJ *> shoot(Wave &wave, PlayerState& playerState) override;

    virtual std::string serialize() override;

    PNJ* get_closest_pnj(Wave& wave);

    std::string getType() override;
};


#endif //PROJET_SNIPERTOWER_HPP
