#ifndef PROJET_ABSTRACTTOWER_H
#define PROJET_ABSTRACTTOWER_H

#include "../common/Position.hpp"
#include "PNJ.hpp"
#include <string>

class AbstractTower {

protected:

    int owner; // player ID
    const int price;
    int radius;
    Position position;

public:

    virtual void shoot(PNJ target) = 0; // HAS TO BE DEFINED BY INHERITORS

    virtual int getOwner() const;

    virtual void setOwner(int owner);

    virtual const int getPrice() const;

    virtual int getRadius() const;

    virtual void setRadius(int radius);

    virtual Position getPosition() const;

    //The position is defined in the map class
    virtual void setPosition(Position position);

    virtual std::string serialize();
};

#endif // PROJET_ABSTRACTTOWER_H
