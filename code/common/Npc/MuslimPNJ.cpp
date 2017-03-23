//
// Created by titi on 18/03/17.
//

#include "MuslimPNJ.h"

MuslimPNJ::MuslimPNJ(int direction) : PNJ(direction) {
    healthPoints = MUSLIM_PNJ_STARTING_HEALTHPOINTS;
    damage = MUSLIM_PNJ_DAMAGE;
    value = MUSLIM_PNJ_VALUE;
    typeOfPNJ = MUSLIM_PNJ_STR;
}
MuslimPNJ::MuslimPNJ(Position position, int healthPoints, int direction)
        : PNJ(position, healthPoints, direction) { typeOfPNJ = MUSLIM_PNJ_STR; }

MuslimPNJ::MuslimPNJ(const Position &position, int healthPoints, const Position &last_pos, int direction)
        : PNJ(position, healthPoints, last_pos, direction) { typeOfPNJ = MUSLIM_PNJ_STR; }




