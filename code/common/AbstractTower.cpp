#include "AbstractTower.hpp"

int AbstractTower::getOwner() const { return owner; }

void AbstractTower::setOwner(int owner) { this->owner = owner; }

const int AbstractTower::getPrice() const { return price; }

const int AbstractTower::getRadius() const { return radius; }

void AbstractTower::setRadius(int radius) { this->radius = radius; }

Position AbstractTower::getPosition() const { return position; }

void AbstractTower::setPosition(Position position) { this->position = position; }