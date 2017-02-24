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

    bool operator==(const Position &rhs) const;

    bool operator!=(const Position &rhs) const;
};

#endif // POSITION_HPP