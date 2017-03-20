

#include "GunTower.hpp"
#include <cmath>

GunTower::GunTower(const Position &position, int level) :
        AttackTower::AttackTower(position, GUN_TOWER_DAMAGE, GUN_TOWER_PRICE, GUN_TOWER_RANGE, level) {}

const std::vector<PNJ *> GunTower::shoot(Wave &wave) {
    PNJ *target;
    std::vector<PNJ *> killed;
    target = get_closest_pnj(wave);
    if ((target != nullptr) && (!target->isInPlayerBase()) && (target->getHealthPoints() > 0)) {
        dealDamageTo(*target);
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

PNJ *GunTower::get_closest_pnj(Wave &wave) {
    int dist;
    int best_dist = 1 << 30;
    PNJ *closest_pnj = nullptr;
    for (auto pnj: wave.getPnjs()) {
        int distance_x = getPosition().getX() - pnj->getPosition().getX();
        int distance_y = getPosition().getY() - pnj->getPosition().getY();

        dist = ((distance_x) * (distance_x)) + (distance_y * distance_y);
        if (dist < best_dist) {
            best_dist = dist;
            closest_pnj = pnj;
        }
    }
    if (sqrt(best_dist) > getRange()) {
        closest_pnj = nullptr;

    }

    return closest_pnj;
}

std::string GunTower::getType() {
    return GUN_TOWER_STR;
}
