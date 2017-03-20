#ifndef PROJET_ABSTRACTTOWER_H
#define PROJET_ABSTRACTTOWER_H

#include "../common/Position.hpp"
#include "PNJ.hpp"
#include "Wave.hpp"
#include <string>

#define LEVEL_MAX 5

class Wave;
class PNJ;

class AbstractTower {

protected:

    int quadrant;
    const int price;
    float range;
    Position position;
    int level;

public:

    AbstractTower(Position position, int price, float range, int level);

    int getQuadrant() const;

    int getLevel() const;

    bool upgrade();

    virtual ~AbstractTower() = default;

    virtual const std::vector<PNJ *>& shoot(Wave& wave) = 0; // HAS TO BE DEFINED BY INHERITORS
    virtual std::string getType() = 0;

    int getOwner() const;
    void setOwner(int newOwner);

    int getPrice() const;
    float getRange() const;

    Position getPosition() const;

    virtual std::string serialize();

    bool operator==(const AbstractTower &rhs) const;

    bool operator!=(const AbstractTower &rhs) const;
};

#endif // PROJET_ABSTRACTTOWER_H
