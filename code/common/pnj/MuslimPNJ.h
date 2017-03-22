//
// Created by titi on 18/03/17.
//
#include "PNJ.hpp"
#ifndef PROJET_MUSLIMPNJ_H
#define PROJET_MUSLIMPNJ_H


class MuslimPNJ : public PNJ  {
public:
    MuslimPNJ(int direction);
    MuslimPNJ(Position position, int healthPoints, int direction);
    MuslimPNJ(const Position &position, int healthPoints, const Position &last_pos, int direction);

};


#endif //PROJET_MUSLIMPNJ_H
