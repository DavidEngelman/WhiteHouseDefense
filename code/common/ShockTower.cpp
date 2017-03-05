//
// Created by jepsiko on 05/03/17.
//

#include "ShockTower.hpp"
#include <cmath>
#include <iostream>

ShockTower::ShockTower(const Position &position) :
        AttackTower(position, SHOCK_TOWER_DAMAGE, SHOCK_TOWER_PRICE, SHOCK_TOWER_RANGE) {}

int ShockTower::shoot(Wave &wave) {
    std::vector<PNJ> targets;
    int killed = 0;
    targets = get_targets(wave);
    for (auto &target : targets) {
        dealDamageTo(target);
        std::cout << target.serialize() << std::endl;
        if (target.getHealthPoints() <= 0) {
            killed += 1;
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
    //serialized_me.insert(0, std::to_string(damageAmount));
    serialized_me.insert(0, SHOCK_TOWER_STR);

    return serialized_me;
}

std::vector<PNJ> &ShockTower::get_targets(Wave &wave) {
    double dist;
    std::vector<PNJ> &targets = wave.getPnjs();
    for (PNJ &pnj: targets) {
        int distance_x = getPosition().getX() - pnj.getPosition().getX();
        int distance_y = getPosition().getY() - pnj.getPosition().getY();

        dist = sqrt(((distance_x) * (distance_x)) + (distance_y * distance_y));
        if (dist < getRange()) {
            targets.push_back(pnj);
        }
    }

    return targets;
}