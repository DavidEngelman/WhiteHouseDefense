#include "PNJ.hpp"


PNJ::PNJ(Position position, int healthPoints):
        position(position), healthPoints(healthPoints),
        movementSpeed(PNJ_STARTING_MOVESPEED), direction(direction),
        last_position(Position(-1000,-1000)) {

}

PNJ::PNJ(int direction): position(Position(15, 15)), healthPoints(PNJ_STARTING_HEALTHPOINTS),
                         movementSpeed(PNJ_STARTING_MOVESPEED), direction(direction),
                         last_position(Position(-1000,-1000)) {}


PNJ::PNJ(Position position, int healthPoints, int movementSpeed, Position last_pos, int direction) :
        position(position), healthPoints(healthPoints), movementSpeed(movementSpeed), last_position(last_pos),
        direction(direction) {}

void PNJ::advance(Map& map) {
    Direction move;
    Position current_position = getPosition();

    if (can_go_forward(map)){
        move = get_forward_direction();
    }

    else if (can_go_left(map)){
        move = get_left_direction();
    }

    else if (can_go_right(map)){
        move = get_right_direction();
    }

    if (move.x > 1 || move.x < -1 || move.y > 1 || move.y < -1) return;

    // TODO: gerer le cas ou il est à la frontiere (ne rien faire)

    // Les PNJS bougent à chaque tick (ce qui n'est pas forcement une bonne idée si le tick est trop rapide)

    Position new_position = Position(getPosition().getX() + move.x, getPosition().getY() + move.y);
    setPosition(new_position);

    setLast_position(current_position);

}

void PNJ::setLast_position(const Position &last_position) {
    PNJ::last_position = last_position;
}

int PNJ::getDirection() const {
    return direction;
}

const Position &PNJ::getLast_position() const {
    return last_position;
}

int PNJ::getHealthPoints() const {
    return this->healthPoints;
}

void PNJ::receiveDamage(int damageAmount) {
    if (healthPoints < damageAmount) healthPoints = 0;
    else healthPoints -= damageAmount;
}

bool PNJ::isDead() {
    return getHealthPoints() <= 0;
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

bool PNJ::can_go_forward(Map& map) {
    Direction dir = get_forward_direction();

    Position forward_pos = Position(getPosition().getX() + dir.x, getPosition().getY() + dir.y);

    return map.isPath(forward_pos);


}

bool PNJ::can_go_left(Map& map) {
    Direction dir = get_left_direction();

    Position left_pos = Position(getPosition().getX() + dir.x, getPosition().getY() + dir.y);

    return map.isPath(left_pos) && left_pos != getLast_position();


}

bool PNJ::can_go_right(Map& map) {
    Direction dir = get_right_direction();

    Position right_pos = Position(getPosition().getX() + dir.x, getPosition().getY() + dir.y);

    return map.isPath(right_pos) && right_pos != getLast_position();


}

Direction PNJ::get_forward_direction() {
    Direction move;

    if (direction == 0) { // wave du haut

        move.x = 0;
        move.y = -1;
        return move;

    } else if (direction == 1) { // wave de droite

        move.x = 1;
        move.y = 0;
        return move;

    } else if (direction == 2) { // wave du bas

        move.x = 0;
        move.y = 1;
        return move;

    } else if (direction == 3) { // wave de gauche

        move.x = -1;
        move.y = 0;
        return move;

    }

}

Direction PNJ::get_right_direction() {
    Direction move;

    if (getDirection() == 0) { // wave du haut

        move.x = 1;
        move.y = 0;
        return move;

    } else if (getDirection() == 1) { // wave de droite

        move.x = 0;
        move.y = 1;
        return move;

    } else if (getDirection() == 2) { // wave du bas

        move.x = -1;
        move.y = 0;
        return move;

    } else if (getDirection() == 3) { // wave de gauche

        move.x = 0;
        move.y = -1;
        return move;

    }
}


Direction PNJ::get_left_direction() {
    Direction move;

    if (getDirection() == 0) { // wave du haut

        move.x = -1;
        move.y = 0;
        return move;

    } else if (getDirection() == 1) { // wave de droite

        move.x = 0;
        move.y = -1;
        return move;

    } else if (getDirection() == 2) { // wave du bas

        move.x = 1;
        move.y = 0;
        return move;

    } else if (getDirection() == 3) { // wave de gauche

        move.x = 0;
        move.y = 1;
        return move;

    }
}

std::string PNJ::serialize() {std::string serialized_me;

    serialized_me += "," + std::to_string(getPosition().getX()) + "," + std::to_string(getPosition().getY()) +
            std::to_string(getHealthPoints());

    return serialized_me;
}

bool PNJ::operator==(const PNJ &rhs) const {
    return *this == rhs;
}

bool PNJ::operator!=(const PNJ &rhs) const {
    return !(rhs == *this);
}

bool PNJ::isInPlayerBase() {
    return (direction == NORTH && getPosition().getY() == 0)
           ||
           (direction == EAST && getPosition().getX() == 30)
           ||
           (direction == SOUTH && getPosition().getY() == 30)
           ||
           (direction == WEST && getPosition().getX() == 0);
}

void PNJ::setHealthPoints(int newHp) {
    healthPoints = newHp;
}
