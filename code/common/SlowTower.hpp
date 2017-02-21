#ifndef PROJET_SLOWTOWER_HPP
#define PROJET_SLOWTOWER_HPP


#include "AbstractTower.hpp"

class SlowTower : public AbstractTower{

private:

    int speedReduction;

public:

    SlowTower(int speedReduction);

    virtual ~SlowTower() = default;

    virtual std::string serialize() override;

    virtual int getSpeedReduction() const;

    virtual void setSpeedReduction(int newSpeedReduction);

    virtual void shoot(PNJ target) override;

    virtual void reduceMovementSpeedOf(PNJ target);


};


#endif //PROJET_SLOWTOWER_HPP
