#include "PNJ.hpp"
#ifndef PROJET_MUSLIMPNJ_H
#define PROJET_MUSLIMPNJ_H


class MuslimPNJ : public PNJ  {
public:
    MuslimPNJ(int direction);
    MuslimPNJ(Position position, Position transitionPosition, int healthPoints, int direction, int isFrozen);
};


#endif //PROJET_MUSLIMPNJ_H
