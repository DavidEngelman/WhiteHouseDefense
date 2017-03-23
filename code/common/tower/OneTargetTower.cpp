

#include <cmath>
#include "OneTargetTower.hpp"

OneTargetTower::OneTargetTower(const Position &position, int price, float range, int level) :
        AbstractTower(position, price, range, level) {}


PNJ* OneTargetTower::getClosestPNJ(Wave &wave) {
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

OneTargetTower::OneTargetTower() : AbstractTower(Position(0, 0), 0, 0, 0) {}
