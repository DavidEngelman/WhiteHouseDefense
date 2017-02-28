#include <cmath>
#include <iostream>
#include "AbstractTower.hpp"

AbstractTower::AbstractTower(Position position, int price, int range):
        position(position), price(price), quadrant(Map::computeQuadrant(position)), range(range), level(0) {
}

PNJ* AbstractTower::get_closest_pnj(Wave &wave) {
    int dist;
    int best_dist = 1 << 30;
    PNJ* closest_pnj = nullptr;
    for (PNJ& pnj: wave.getPnjs()){
        int distance_x = getPosition().getX() - pnj.getPosition().getX();
        int distance_y = getPosition().getY() - pnj.getPosition().getY();

        dist = ((distance_x) * (distance_x)) + (distance_y * distance_y);
        if (dist < best_dist){
            best_dist = dist;
            closest_pnj = &pnj;
        }
    }
    if (sqrt(best_dist) > getRange()){
        closest_pnj = nullptr;

    }

    return closest_pnj;
}

int AbstractTower::getLevel() const { return level; }

int AbstractTower::getOwner() const { return quadrant; }

void AbstractTower::setOwner(int newOwner) { quadrant = newOwner; }

int AbstractTower::getPrice() const { return price; }

float AbstractTower::getRange() const { return level*range/10 + range; } // +10% de radius par upgrade

Position AbstractTower::getPosition() const { return position; }

std::string AbstractTower::serialize() {

    std::string serialized_me;

    serialized_me +=  position.serialize();

    return serialized_me;
}

int AbstractTower::getQuadrant() const {
    return quadrant;
}

bool AbstractTower::upgrade() {
    if (level < LEVEL_MAX) {
        level++;
        // TODO : dépenser de l'argent du joueur
        return true;
    }
    return false;
}

bool AbstractTower::operator==(const AbstractTower &rhs) const {
    return position == rhs.position;
}

bool AbstractTower::operator!=(const AbstractTower &rhs) const {
    return !(rhs == *this);
}
