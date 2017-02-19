#include "SlowTower.hpp"

int SlowTower::getSpeedReduction() const { return this->speedReduction; }

void SlowTower::setSpeedReduction(int speedReduction) { this->speedReduction = speedReduction; }

void SlowTower::reduceMovementSpeedOf(PNJ pnj) { pnj.receiveMovementPenalty(this->getSpeedReduction()); }
