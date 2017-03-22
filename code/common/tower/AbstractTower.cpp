#include <cmath>
#include <iostream>
#include "AbstractTower.hpp"

AbstractTower::AbstractTower(Position position, int price, float range, int level):
        position(position), price(price), quadrant(Map::computeQuadrant(position)), range(range), level(level) {
}

int AbstractTower::getLevel() const { return level; }

int AbstractTower::getOwner() const { return quadrant; }

void AbstractTower::setOwner(int newOwner) { quadrant = newOwner; }

int AbstractTower::getPrice() const { return (level -1)*price/10 + price; }

float AbstractTower::getRange() const { return level*range/10 + range; } // +10% de radius par upgrade

Position AbstractTower::getPosition() const { return position; }

std::string AbstractTower::serialize() {

    std::string serialized_me;

    serialized_me +=  std::to_string(level) + ",";
    serialized_me +=  position.serialize();

    return serialized_me;
}

int AbstractTower::getQuadrant() const {
    return quadrant;
}

bool AbstractTower::upgrade() {
    if (level < LEVEL_MAX) {
        level++;
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
