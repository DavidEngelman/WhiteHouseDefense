

#include "GunTower.hpp"
#include <cmath>

GunTower::GunTower(const Position &position, int level) :
        AttackTower::AttackTower(position, GUN_TOWER_DAMAGE, GUN_TOWER_PRICE, GUN_TOWER_RANGE, level),
        OneTargetTower::OneTargetTower(position, GUN_TOWER_PRICE, GUN_TOWER_RANGE, level) {}

const std::vector<PNJ *> GunTower::shoot(Wave &wave, PlayerState& playerState) {
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

std::string GunTower::serialize() {
    /*
     * Une GunTower sérialisée est comme ceci : "GunTower,x,y;"
     */
    std::string serialized_me = AbstractTower::serialize();
    serialized_me.insert(0, ",");
    //serialized_me.insert(0, std::to_string(damageAmount));
    serialized_me.insert(0, GUN_TOWER_STR);

    return serialized_me;
}

std::string GunTower::getType() {
    return GUN_TOWER_STR;
}
