#ifndef PROJET_SLOWTOWER_HPP
#define PROJET_SLOWTOWER_HPP


#include "AbstractTower.hpp"

class SlowTower : public AbstractTower{

private:

    int speedReduction;

public:

    virtual int getSpeedReduction() const;

    virtual void setSpeedReduction(int speedReduction);

    virtual void shoot(PNJ target);

    virtual void reduceMovementSpeedOf(PNJ target);
};


#endif //PROJET_SLOWTOWER_HPP
