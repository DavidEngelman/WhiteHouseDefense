//
// Created by Alexandre on 19-02-17.
//

#include "PNJ.hpp"
#include "SlowTower.hpp"
#include "AttackTower.hpp"
#include "Position.hpp"

PNJ::PNJ(){
    healthPoints = 100;
    movementSpeed = 100;
    position(0,0);
}

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

Position PNJ::setPosition(int x, int y) {
    this->position.setX(x);
    this->postition.setY(y);
}