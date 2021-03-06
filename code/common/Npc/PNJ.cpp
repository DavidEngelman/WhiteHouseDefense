#include <iostream>
#include "PNJ.hpp"

// Constructor used when unserializing
PNJ::PNJ(Position position, Position transitionPosition, int healthPoints, int direction, int frozen) :
        position(position), transitionPosition(transitionPosition), healthPoints(healthPoints),
        quadrant(direction), damage(-1), value(-1), freezeTicksLeft(0),
        last_position(Position(-1000, -1000)),
        inTransition(false), frozen(frozen) {}

PNJ::PNJ(int direction) :
        position(Position(SIZE / 2, SIZE / 2)),
        transitionPosition(Position(SIZE / 2 * TILES_SIZE, SIZE / 2 * TILES_SIZE)),
        quadrant(direction), freezeTicksLeft(0),
        last_position(Position(-1000, -1000)),
        inTransition(false), frozen(0) {}


void PNJ::get_random_direction() {
    int rand_mov = rand() % 2;
    if (rand_mov == 0)
        get_left_direction();
    else
        get_right_direction();
}

void PNJ::advance(Map &map) {
    if (freezeTicksLeft > 0) { // The PNJ doesn't move if it's freezed
        freezeTicksLeft -= 1;
        if (freezeTicksLeft == 0) {
            frozen = 0;
        }
        return;
    }

    if (!isInTransition()) {
        if (can_go_forward(map)) {
            get_forward_direction();
        } else if (can_go_left(map) && can_go_right(map)) {
            get_random_direction();
        } else if (can_go_left(map)) {
            get_left_direction();
        } else if (can_go_right(map)) {
            get_right_direction();
        } else if (can_go_backward(map)) {
            get_backward_direction();
        } else {
            std::cout << "No direction was good for PNJ in ("
                      << position.getX() << ","
                      << position.getY() << ")"
                      << " and the transition position ("
                      << transitionPosition.getX() << ","
                      << transitionPosition.getY() << ")"
                      << std::endl;
        }

        setLastPosition(getPosition());
        inTransition = true;
    }

    Position current_position = getTransitionPosition();
    Position new_position = Position(current_position.getX() + direction.x, current_position.getY() + direction.y);
    setTransitionPosition(new_position);
}

void PNJ::setLastPosition(const Position &last_position) {
    PNJ::last_position = last_position;
}

int PNJ::getQuadrant() const {
    return quadrant;
}

const Position &PNJ::getLast_position() const {
    return last_position;
}

int PNJ::getHealthPoints() const {
    return this->healthPoints;
}

int PNJ::receiveDamage(int damageAmount) {
    int receivedDamage = 0;
    if (healthPoints < damageAmount) {
        healthPoints = 0;
        receivedDamage = healthPoints;
    } else {
        healthPoints -= damageAmount;
        receivedDamage = damageAmount;
    }
    return receivedDamage;
}

bool PNJ::isDead() {
    return getHealthPoints() <= 0;
}

const Position &PNJ::getPosition() const {
    return this->position;
}

void PNJ::setPosition(Position &position) {
    this->position = position;
}

bool PNJ::can_go_forward(Map &map) {
    get_forward_direction();
    Position forward_pos = Position(getPosition().getX() + direction.x, getPosition().getY() + direction.y);
    return (map.isPath(forward_pos) || map.isBase(forward_pos)) && forward_pos != getLast_position();
}

bool PNJ::can_go_left(Map &map) {
    get_left_direction();
    Position left_pos = Position(getPosition().getX() + direction.x, getPosition().getY() + direction.y);
    return (map.isPath(left_pos) || map.isBase(left_pos)) && left_pos != getLast_position();
}

bool PNJ::can_go_right(Map &map) {
    get_right_direction();
    Position right_pos = Position(getPosition().getX() + direction.x, getPosition().getY() + direction.y);
    return (map.isPath(right_pos) || map.isBase(right_pos)) && right_pos != getLast_position();
}

bool PNJ::can_go_backward(Map &map) {
    get_backward_direction();
    Position back_pos = Position(getPosition().getX() + direction.x, getPosition().getY() + direction.y);
    return (map.isPath(back_pos) || map.isBase(back_pos)) && back_pos != getLast_position();
}

void PNJ::get_forward_direction() {
    if (getQuadrant() == NORTH) {
        direction.x = 0;
        direction.y = -1;
    } else if (getQuadrant() == EAST) {
        direction.x = 1;
        direction.y = 0;
    } else if (getQuadrant() == SOUTH) {
        direction.x = 0;
        direction.y = 1;
    } else {
        direction.x = -1;
        direction.y = 0;
    }
}

void PNJ::get_right_direction() {
    if (getQuadrant() == NORTH) {
        direction.x = 1;
        direction.y = 0;
    } else if (getQuadrant() == EAST) {
        direction.x = 0;
        direction.y = 1;
    } else if (getQuadrant() == SOUTH) {
        direction.x = -1;
        direction.y = 0;
    } else {
        direction.x = 0;
        direction.y = -1;
    }
}


void PNJ::get_left_direction() {
    if (getQuadrant() == NORTH) {
        direction.x = -1;
        direction.y = 0;
    } else if (getQuadrant() == EAST) {
        direction.x = 0;
        direction.y = -1;
    } else if (getQuadrant() == SOUTH) {
        direction.x = 1;
        direction.y = 0;
    } else {
        direction.x = 0;
        direction.y = 1;
    }
}

void PNJ::get_backward_direction() {
    if (getQuadrant() == NORTH) {
        direction.x = 0;
        direction.y = 1;
    } else if (getQuadrant() == EAST) {
        direction.x = -1;
        direction.y = 0;
    } else if (getQuadrant() == SOUTH) {
        direction.x = 0;
        direction.y = -1;
    } else {
        direction.x = 1;
        direction.y = 0;
    }
}

std::string PNJ::serialize() {
    std::string serialized_me;

    serialized_me +=
            std::to_string(getPosition().getX()) + "," +
            std::to_string(getPosition().getY()) + "," +
            std::to_string(getTransitionPosition().getX()) + "," +
            std::to_string(getTransitionPosition().getY()) + "," +
            std::to_string(getHealthPoints()) + "," +
            getType() + "," +
            std::to_string(frozen) + "|";

    return serialized_me;
}

bool PNJ::operator==(const PNJ &rhs) const {
    return *this == rhs;
}

bool PNJ::operator!=(const PNJ &rhs) const {
    return !(rhs == *this);
}

bool PNJ::isInPlayerBase() {
    return (quadrant == NORTH && getPosition().getY() == 0)
           ||
           (quadrant == EAST && getPosition().getX() == SIZE - 1)
           ||
           (quadrant == SOUTH && getPosition().getY() == SIZE - 1)
           ||
           (quadrant == WEST && getPosition().getX() == 0);
}

void PNJ::setHealthPoints(int newHp) {
    healthPoints = newHp;
}

int PNJ::getDamage() {
    return damage;
}

int PNJ::getValue() {
    return value;
}

const std::string &PNJ::getType() {
    return typeOfPNJ;
}

void PNJ::freeze() {
    frozen = 1;
    freezeTicksLeft = NUM_FREEZE_TICKS_FOR_PNJ;
}

const Position &PNJ::getTransitionPosition() const {
    return transitionPosition;
}

bool PNJ::isInTransition() {
    return inTransition;
}

void PNJ::setTransitionPosition(Position &position) {
    transitionPosition = position;

    if ((position.getX() % TILES_SIZE == 0) && (position.getY() % TILES_SIZE == 0)) {
        inTransition = false;
        Position currentPos = Position(position.getX() / TILES_SIZE, position.getY() / TILES_SIZE);
        setPosition(currentPos);
    }
}


