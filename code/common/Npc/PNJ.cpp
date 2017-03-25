#include "PNJ.hpp"
#include <cstdlib>
#include <iostream>


PNJ::PNJ(Position position, int healthPoints, int direction) :
        position(position), healthPoints(healthPoints),
        quadrant(direction), damage(-1), value(-1), freezeTicksLeft(0),
        last_position(Position(-1000, -1000)),
        transitionPosition(Position(-1, -1)),
        inTransition(false) {}

PNJ::PNJ(int direction) :
        position(Position(SIZE / 2, SIZE / 2)),
        quadrant(direction), freezeTicksLeft(0),
        last_position(Position(-1000, -1000)),
        transitionPosition(Position(SIZE / 2 * TILES_SIZE, SIZE / 2 * TILES_SIZE)),
        inTransition(false) {}

PNJ::PNJ(Position position, int healthPoints, Position last_pos, int direction) :
        position(position), healthPoints(healthPoints), last_position(last_pos),
        quadrant(direction), damage(-1), value(-1), freezeTicksLeft(0),
        transitionPosition(Position(-1, -1)),
        inTransition(false) {}

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
        return;
    }


    if (!isInTransition()) {
        std::cout << "pas en transition" << std::endl;
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
        }

        if (direction.x > 1 || direction.x < -1 || direction.y > 1 || direction.y < -1) return;

        setLast_position(getPosition());
        inTransition = true;
    }

    Position current_position = getTransitionPosition();

    Position new_position = Position(current_position.getX() + direction.x, current_position.getY() + direction.y);
    setTransitionPosition(new_position);
}

void PNJ::setLast_position(const Position &last_position) {
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

const Position& PNJ::getPosition() const {
    return this->position;
}

/*
 * The client only receives the transition positions, which have greater precision.
 * For example, the transition X position can vary between 0 and SIZE * TILES_SIZE.
 * This is great for making a smooth path in the GUI.
 *
 * On the console, this doesn't make sense however, so we need to find the equivalent position
 * such that the X and Y coordinate are between 0 and SIZE. This method returns that position.
 *
 * Example: in the GUI, there are 600 possible X values, because there are 30 squares and within
 * those square 20 transition points. Therefore, 0 <= X < 600. On the console, however there
 * are only square (and no transition points), so 0 <= X < 30. This methods transforms a position
 * of the first format into the second format.
 *
 * Position(62, 100) -> Position(62 // 20, 100 // 20) = Position(3, 5).
 */
const Position PNJ::getNormalizedPosition() const  {
    return Position(position.getX() / TILES_SIZE, position.getY() / TILES_SIZE);
}


void PNJ::setPosition(Position& position) {
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
            std::to_string(getTransitionPosition().getX()) + "," +
            std::to_string(getTransitionPosition().getY()) + "," +
            std::to_string(getHealthPoints()) + "," +
            getType() + "|";

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
    freezeTicksLeft = NUM_FREEZE_TICKS_FOR_PNJ;
}

const Position& PNJ::getTransitionPosition() const {
    return transitionPosition;
}

bool PNJ::isInTransition() {
    return inTransition;
}

void PNJ::setTransitionPosition(Position &position) {
    transitionPosition = position;

    if (position.getX() % TILES_SIZE == 0 && position.getY() % TILES_SIZE == 0) {
        inTransition = false;
        Position currentPos = Position(position.getX()/TILES_SIZE, position.getY()/TILES_SIZE);
        setPosition(currentPos);
    }
}


