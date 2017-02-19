#ifndef PROJET_ABSTRACTTOWER_H
#define PROJET_ABSTRACTTOWER_H

#include "../common/Position.hpp"
#include "PNJ.hpp"

class AbstractTower {

private:

    int owner; // player ID
    int price;
    Position position;

public:

    virtual void shoot(PNJ target); // HAS TO BE DEFINED BY INHERITORS

    // The price of a tower must be a constant
    virtual int getOwner() const;

    virtual void setOwner(int owner);

    //The position is defined in the map class
    virtual int getPrice() const;

    virtual void setPrice(int price);

    virtual Position getPosition() const;

    virtual void setPosition(Position position);
};

#endif // PROJET_ABSTRACTTOWER_H
