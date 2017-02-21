
#include "Position.hpp"

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
