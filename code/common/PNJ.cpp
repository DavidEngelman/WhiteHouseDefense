#include "PNJ.hpp"


PNJ::PNJ(): PNJ(Position(100, 100), 100, 100){
}

PNJ::PNJ(Position position, int healthPoints, int movementSpeed) :
position(position), healthPoints(healthPoints), movementSpeed(movementSpeed) {}



int PNJ::getHealthPoints() const {
    return this->healthPoints;
}

void PNJ::receiveDamage(int damageAmount) {
    (this->healthPoints -= damageAmount < 0) ? (this->healthPoints = 0) : (this->healthPoints -= damageAmount);

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


bool PNJ::can_go_forward(int wave_id, Position &current_pos) {
    Direction dir = get_forward_direction(wave_id);

    Position forward_pos = Position(current_pos.getX() + dir.x, current_pos.getY() + dir.y);

    if (map.is_path(forward_pos)) {
        return true;
    }
    return false;


}

bool PNJ::can_go_left(int wave_id, Position &current_pos, Position &last_pos) {
    Direction dir = get_left_direction(wave_id);

    Position letf_pos = Position(current_pos.getX() + dir.x, current_pos.getY() + dir.y);

    if (map.is_path(letf_pos) && letf_pos != last_pos) {
        //TODO implement != for position
        return true;
    }
    return false;


}

bool PNJ::can_go_right(int wave_id, Position &current_pos, Position &last_pos) {
    Direction dir = get_right_direction(wave_id);

    Position right_pos = Position(current_pos.getX() + dir.x, current_pos.getY() + dir.y);

    if (map.is_path(right_pos) && right_pos != last_pos) {
        //TODO implement != for position
        return true;
    }
    return false;


}

Direction PNJ::get_forward_direction(int wave_id) {
    Direction direction;

    if (wave_id == 0) { // wave du haut

        direction.x = 0;
        direction.y = 1;
        return direction;

    } else if (wave_id == 1) { // wave de droite

        direction.x = 1;
        direction.y = 0;
        return direction;

    } else if (wave_id == 2) { // wave du bas

        direction.x = 0;
        direction.y = -1;
        return direction;

    } else if (wave_id == 3) { // wave de gauche

        direction.x = 1;
        direction.y = 0;
        return direction;

    }

}

Direction PNJ::get_right_direction(int wave_id) {
    Direction direction;

    if (wave_id == 0) { // wave du haut

        direction.x = 1;
        direction.y = 0;
        return direction;

    } else if (wave_id == 1) { // wave de droite

        direction.x = 0;
        direction.y = -1;
        return direction;

    } else if (wave_id == 2) { // wave du bas

        direction.x = 1;
        direction.y = 0;
        return direction;

    } else if (wave_id == 3) { // wave de gauche

        direction.x = 0;
        direction.y = 1;
        return direction;

    }
}

Direction PNJ::get_left_direction(int wave_id) {
    Direction direction;

    if (wave_id == 0) { // wave du haut

        direction.x = -1;
        direction.y = 0;
        return direction;

    } else if (wave_id == 1) { // wave de droite

        direction.x = 0;
        direction.y = 1;
        return direction;

    } else if (wave_id == 2) { // wave du bas

        direction.x = 1;
        direction.y = 0;
        return direction;

    } else if (wave_id == 3) { // wave de gauche

        direction.x = 0;
        direction.y = -1;
        return direction;

    }
}
