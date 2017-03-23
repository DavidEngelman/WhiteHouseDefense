//
// Created by jepsiko on 03/03/17.
//

#include "SniperTower.hpp"
#include <cmath>

SniperTower::SniperTower(const Position &position, int level) :
        OneTargetTower::OneTargetTower(),
        AttackTower::AttackTower(SNIPER_TOWER_DAMAGE),
        AbstractTower::AbstractTower(position, GUN_TOWER_PRICE, GUN_TOWER_RANGE, level) {}

const std::vector<PNJ *> SniperTower::shoot(Wave &wave, PlayerState& playerState) {
    PNJ *target;
    std::vector<PNJ *> killed;
    target = getClosestPNJ(wave);
    if ((target != nullptr) && (!target->isInPlayerBase()) && (target->getHealthPoints() > 0)) {
        dealDamageTo(*target, playerState);
        if (target->getHealthPoints() <= 0) {
            killed.push_back(target);
        }
    }
    return killed;
}

std::string SniperTower::serialize() {
    /*
     * Une SniperTower sérialisée est comme ceci : "SniperTower,x,y;"
     */
    std::string serialized_me = AbstractTower::serialize();
    serialized_me.insert(0, ",");
    //serialized_me.insert(0, std::to_string(damageAmount));
    serialized_me.insert(0, SNIPER_TOWER_STR);

    return serialized_me;
}

std::string SniperTower::getType() {
    return SNIPER_TOWER_STR;
}

