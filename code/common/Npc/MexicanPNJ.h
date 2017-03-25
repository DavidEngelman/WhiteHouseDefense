#ifndef PROJET_MEXICANPNJ_H
#define PROJET_MEXICANPNJ_H


#include "PNJ.hpp"

class MexicanPNJ : public PNJ {
public:
    MexicanPNJ(int direction);
    MexicanPNJ(Position transitionPosition, int healthPoints, int direction);
};


#endif //PROJET_MEXICANPNJ_H
