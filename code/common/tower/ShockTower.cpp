//
// Created by jepsiko on 05/03/17.
//

#include "ShockTower.hpp"
#include <cmath>
#include <iostream>

ShockTower::ShockTower(const Position &position, int level) :
        AttackTower(position, SHOCK_TOWER_DAMAGE, SHOCK_TOWER_PRICE, SHOCK_TOWER_RANGE, level) {}

const std::vector<PNJ*> ShockTower::shoot(Wave &wave, PlayerState& playerState) {
    std::vector<PNJ*> targets;
    std::vector<PNJ*> killed;
    targets = get_targets(wave);
    for (auto &target : targets) {
        dealDamageTo(*target, playerState);
        if (target->getHealthPoints() <= 0) {
            killed.push_back(target);
        }
    }
    return killed;
}

std::string ShockTower::serialize() {
    /*
     * Une ShockTower sérialisée est comme ceci : "ShockTower,x,y;"
     */
    std::string serialized_me = AbstractTower::serialize();
    serialized_me.insert(0, ",");
    serialized_me.insert(0, SHOCK_TOWER_STR);

    return serialized_me;
}

std::vector<PNJ*> ShockTower::get_targets(Wave &wave) {
    double dist;
    std::vector<PNJ*> targets;
    for (auto &pnj: wave.getPnjs()) {
        int distance_x = getPosition().getX() - pnj->getPosition().getX();
        int distance_y = getPosition().getY() - pnj->getPosition().getY();

        dist = sqrt(((distance_x) * (distance_x)) + (distance_y * distance_y));
        if (dist < getRange()) {
            targets.push_back(pnj);
        }
    }

    return targets;
}

std::string ShockTower::getType() {
    return SHOCK_TOWER_STR;
}
