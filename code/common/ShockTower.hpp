//
// Created by jepsiko on 05/03/17.
//

#ifndef PROJET_SHOCKTOWER_HPP
#define PROJET_SHOCKTOWER_HPP


#include "AttackTower.hpp"

class ShockTower : public AttackTower {

public:
    ShockTower(const Position &position);

    ~ShockTower() = default;

    virtual int shoot(Wave &wave) override;

    virtual std::string serialize() override;

    std::vector<PNJ> &get_targets(Wave& wave);
};


#endif //PROJET_SHOCKTOWER_HPP
