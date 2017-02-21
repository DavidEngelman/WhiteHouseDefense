#ifndef POSITION_HPP
#define POSITION_HPP

#include <iosfwd>
#include <string>

class Position {

public:
    int x;
    int y;

    int getY() const;

    void setY(int y);

    int getX() const;

    void setX(int x);

    Position(int _x, int _y);
};

#endif // POSITION_HPP