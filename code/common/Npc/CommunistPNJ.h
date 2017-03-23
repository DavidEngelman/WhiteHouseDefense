//
// Created by titi on 20/03/17.
//

#ifndef PROJET_COMMUNISTPNJ_H
#define PROJET_COMMUNISTPNJ_H


#include "PNJ.hpp"

class CommunistPNJ : public PNJ {
public:
    CommunistPNJ(int direction);
    CommunistPNJ(Position position, int healthPoints, int direction);
    CommunistPNJ(const Position &position, int healthPoints, const Position &last_pos, int direction);
};


#endif //PROJET_COMMUNISTPNJ_H
