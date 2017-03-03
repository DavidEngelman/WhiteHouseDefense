
#include "Position.hpp"

Position::Position() : x(0), y(0) {};

Position::Position(int _x, int _y) : x(_x), y(_y) {}

int Position::getX() const {
    return x;
}

void Position::setX(int x) {
    Position::x = x;
}

int Position::getY() const {
    return y;
}

void Position::setY(int y) {
    Position::y = y;
}

bool Position::operator==(const Position &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Position::operator!=(const Position &rhs) const {
    return !(rhs == *this);
}

std::string Position::serialize() {
    std::string serialized_me;

    serialized_me += std::to_string(getX()) + "," + std::to_string(getY()) +";";

    return serialized_me;

}
