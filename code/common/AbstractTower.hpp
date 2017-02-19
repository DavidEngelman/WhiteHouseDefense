#ifndef PROJET_ABSTRACTTOWER_H
#define PROJET_ABSTRACTTOWER_H

#include "../common/Position.hpp"
#include "PNJ.hpp"

class AbstractTower {

private:

    int owner; // player ID
    const int price;
    Position position;

public:

    virtual void shoot(PNJ target); // HAS TO BE DEFINED BY INHERITORS

    virtual int getOwner() const;

    virtual void setOwner(int owner);

    virtual int getPrice() const;

    virtual void setPrice(int price);

    virtual Position getPosition() const;

    //The position is defined in the map class
    virtual void setPosition(Position position);
};

#endif // PROJET_ABSTRACTTOWER_H
