#ifndef POSITION_HPP
#define POSITION_HPP

#include <iosfwd>
#include <string>

class Position {

public:
    int x;
    int y;

    Position();
    Position(int _x, int _y);
};

#endif // POSITION_HPP