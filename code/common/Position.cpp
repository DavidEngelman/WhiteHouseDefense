
#include "Position.hpp"

Position::Position(int x, int y) : _x(x), _y(y) {
}

int Position::getX() {
    return _x;
}

void Position::setX(int x) {
    _x = x;
}

int Position::getY() {
    return _y;
}

void Position::setY(int y) {
    _y = y;
}
