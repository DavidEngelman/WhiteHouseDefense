#ifndef PROJET_ABSTRACTTOWER_H
#define PROJET_ABSTRACTTOWER_H

#include "../common/Position.hpp"
#include "PNJ.hpp"
#include "Wave.h"
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

    AbstractTower(Position position, int price, int radius);

    int getQuadrant() const;

    int getLevel() const;

    bool upgrade();

    virtual ~AbstractTower() = default;

    virtual bool shoot(Wave& wave) = 0; // HAS TO BE DEFINED BY INHERITORS

    PNJ* get_closest_pnj(Wave& wave);

    int getOwner() const;
    void setOwner(int newOwner);

    int getPrice() const;
    float getRange() const;

    Position getPosition() const;

    virtual std::string serialize();
};

#endif // PROJET_ABSTRACTTOWER_H
