//
// Created by titi on 20/03/17.
//

#ifndef PROJET_MEXICANPNJ_H
#define PROJET_MEXICANPNJ_H


#include "PNJ.hpp"

class MexicanPNJ : public PNJ {
public:
    MexicanPNJ(int direction);
    MexicanPNJ(Position position, int healthPoints, int direction);
    MexicanPNJ(const Position &position, int movementSpeed, const Position &last_pos, int direction);

};


#endif //PROJET_MEXICANPNJ_H
