#include "SlowTower.hpp"

int SlowTower::getSpeedReduction() const { return this->speedReduction; }

void SlowTower::setSpeedReduction(int speedReduction) { this->speedReduction = speedReduction; }

void SlowTower::shoot(PNJ target) { this->reduceMovementSpeedOf(target); }

void SlowTower::reduceMovementSpeedOf(PNJ target) { target.receiveMovementPenalty(this->getSpeedReduction()); }
