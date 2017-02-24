#ifndef PROJET_ABSTRACTTOWER_H
#define PROJET_ABSTRACTTOWER_H

#include "../common/Position.hpp"
#include "PNJ.hpp"
#include "Wave.h"
#include <string>

class AbstractTower {

protected:

    int quadrant;
    const int price;
    int radius;
    Position position;

    const int computeQuadrant();

public:

    AbstractTower(Position position, int price, int radius);

    int getQuadrant() const;


    virtual ~AbstractTower() = default;

    virtual void shoot(Wave& wave) = 0; // HAS TO BE DEFINED BY INHERITORS

    PNJ& get_closest_pnj(Wave& wave);

    virtual int getOwner() const;

    virtual void setOwner(int newOwner);

    virtual const int getPrice() const;

    virtual int getRadius() const;

    virtual void setRadius(int newRadius);

    virtual Position getPosition() const;

    //The position is defined in the map class
    virtual void setPosition(Position newPosition);

    virtual std::string serialize();
};

#endif // PROJET_ABSTRACTTOWER_H
