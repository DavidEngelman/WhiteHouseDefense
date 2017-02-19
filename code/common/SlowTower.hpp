#ifndef PROJET_SLOWTOWER_HPP
#define PROJET_SLOWTOWER_HPP


#include "AbstractTower.hpp"

class SlowTower : public AbstractTower{

private:

    int speedReduction;

public:

    virtual int getSpeedReduction() const;

    virtual void setSpeedReduction(int speedReduction);

    virtual void reduceMovementSpeedOf(PNJ pnj);
};


#endif //PROJET_SLOWTOWER_HPP
