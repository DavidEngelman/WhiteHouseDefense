#include "SlowTower.hpp"

SlowTower(int speedReduction): speedReduction(speedReduction) {}

int SlowTower::getSpeedReduction() const { return this->speedReduction; }

void SlowTower::setSpeedReduction(int newSpeedReduction) { speedReduction = newSpeedReduction; }

void SlowTower::shoot(PNJ target) { this->reduceMovementSpeedOf(target); }

void SlowTower::reduceMovementSpeedOf(PNJ target) { target.receiveMovementPenalty(this->getSpeedReduction()); }

std::string SlowTower::serialize() {
    /*
     * Une SlowTower sérialisée est comme ceci : "SlowTower,speedReduction,owner,price,radius,position;"
     */
    std::string serialized_me = AbstractTower::serialize();
    serialized_me.insert(0, ",");
    serialized_me.insert(0, std::to_string(speedReduction));
    serialized_me.insert(0, "SlowTower,");

    return serialized_me;


}