#ifndef POSITION_HPP
#define POSITION_HPP

#include <iosfwd>
#include <string>

class Position {
private:
    int x;
    int y;

public:
    Position();
    Position(int _x, int _y);

    bool operator==(const Position &rhs) const;

    bool operator!=(const Position &rhs) const;

    int getX() const;

    void setX(int x);

    int getY() const;

    void setY(int y);

    std::string serialize();
};

#endif // POSITION_HPP