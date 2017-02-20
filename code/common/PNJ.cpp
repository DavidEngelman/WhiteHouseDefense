#include "PNJ.hpp"

PNJ::PNJ(): PNJ(Position(100, 100), 100, 100){
}

PNJ::PNJ(Position position, int healthPoints, int movementSpeed) :
position(position), healthPoints(healthPoints), movementSpeed(movementSpeed) {}

int PNJ::getHealthPoints() const {
    return this->healthPoints;
}

void PNJ::receiveDamage(int damageAmount) {
    this->healthPoints -= damageAmount;
}

int PNJ::getMovementSpeed() const {
    return this->movementSpeed;
}

void PNJ::setMovementSpeed(int newMovementSpeed) {
    this->movementSpeed = newMovementSpeed;
}

void PNJ::receiveMovementPenalty(int speedReduction) {
    this->movementSpeed -= speedReduction;
}

Position PNJ::getPosition() const {
    return this->position;
}

void PNJ::setPosition(Position position){
    this->position = position;
}
