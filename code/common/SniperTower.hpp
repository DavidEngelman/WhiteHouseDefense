#ifndef PROJET_SNIPERTOWER_HPP
#define PROJET_SNIPERTOWER_HPP


#include "AttackTower.hpp"

class SniperTower : public AttackTower {

public:
    SniperTower(const Position &position);

    ~SniperTower() = default;

    virtual int shoot(Wave &wave) override;

    virtual std::string serialize() override;

    PNJ* get_closest_pnj(Wave& wave);

    std::string getType() override;
};


#endif //PROJET_SNIPERTOWER_HPP
