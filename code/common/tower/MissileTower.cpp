

#include <cmath>
#include <iostream>
#include "MissileTower.hpp"


MissileTower::MissileTower(const Position &position, int level) :
        AttackTower(position, MISSILE_TOWER_DAMAGE, MISSILE_TOWER_PRICE, MISSILE_TOWER_RANGE, level),
        OneTargetTower::OneTargetTower(position, GUN_TOWER_PRICE, GUN_TOWER_RANGE, level) {}

const std::vector<PNJ*> MissileTower::shoot(Wave &wave, PlayerState& playerState) {
    PNJ* closestTarget;
    std::vector<PNJ*> targets;
    std::vector<PNJ*> killed;
    closestTarget = get_closest_pnj(wave);

    if ((closestTarget != nullptr) && (!closestTarget->isInPlayerBase()) && (closestTarget->getHealthPoints() > 0)) {
        dealDamageTo(*closestTarget, playerState);
        if (closestTarget->getHealthPoints() <= 0) {
            killed.push_back(closestTarget);
        }

        targets = get_targets(wave, closestTarget);
        for (auto &target : targets) {
            dealDamageToSubTargets(*target, playerState);
            if (target->getHealthPoints() <= 0) {
                killed.push_back(target);
            }
        }
    }

    return killed;
}

std::string MissileTower::serialize() {
    /*
     * Une MissileTower sérialisée est comme ceci : "MissileTower,x,y;"
     */
    std::string serialized_me = AbstractTower::serialize();
    serialized_me.insert(0, ",");
    serialized_me.insert(0, MISSILE_TOWER_STR);

    return serialized_me;
}

std::vector<PNJ*> MissileTower::get_targets(Wave &wave, PNJ* closestTarget) {
    double dist;
    std::vector<PNJ*> targets;
    for (auto &pnj: wave.getPnjs()) {
        int distance_x = closestTarget->getPosition().getX() - pnj->getPosition().getX();
        int distance_y = closestTarget->getPosition().getY() - pnj->getPosition().getY();

        dist = sqrt(((distance_x) * (distance_x)) + (distance_y * distance_y));
        if (dist < MISSILE_TOWER_SUBRANGE) {
            targets.push_back(pnj);
        }
    }

    return targets;
}

PNJ *MissileTower::get_closest_pnj(Wave &wave) {
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

std::string MissileTower::getType() {
    return MISSILE_TOWER_STR;
}

void MissileTower::dealDamageToSubTargets(PNJ &target, PlayerState& playerState) {
    int damage = std::min(target.getHealthPoints(), MISSILE_TOWER_SUBDAMAGE);
    playerState.incrDamageDealt(damage);
}