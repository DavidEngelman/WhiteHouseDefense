#ifndef PROJET_COMMUNISTPNJ_H
#define PROJET_COMMUNISTPNJ_H


#include "PNJ.hpp"

class CommunistPNJ : public PNJ {
public:
    CommunistPNJ(int direction);
    CommunistPNJ(Position transitionPosition, int healthPoints, int direction, int frozen);
};


#endif //PROJET_COMMUNISTPNJ_H
