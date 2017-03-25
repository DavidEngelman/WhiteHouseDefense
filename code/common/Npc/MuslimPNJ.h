#include "PNJ.hpp"
#ifndef PROJET_MUSLIMPNJ_H
#define PROJET_MUSLIMPNJ_H


class MuslimPNJ : public PNJ  {
public:
    MuslimPNJ(int direction);
    MuslimPNJ(Position transitionPosition, int healthPoints, int direction);
};


#endif //PROJET_MUSLIMPNJ_H
