#include "AbstractTower.hpp"

virtual int AbstractTower::getOwner() const { return owner; }

virtual void AbstractTower::setOwner(int owner) { this->owner = owner; }

virtual const int AbstractTower::getPrice() const { return price; }

virtual Position AbstractTower::getPosition() const { return position; }

virtual void AbstractTower::setPosition(Position position) { this->position = position; }