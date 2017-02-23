#ifndef POSITION_HPP
#define POSITION_HPP

#include <iosfwd>
#include <string>

class Position {

public:
    int x;
    int y;

    Position();
    
    int getY() const;

    void setY(int y);

    int getX() const;

    void setX(int x);

    Position(int _x, int _y);

    bool operator==(const Position &rhs) const;

    bool operator!=(const Position &rhs) const;
};

#endif // POSITION_HPP