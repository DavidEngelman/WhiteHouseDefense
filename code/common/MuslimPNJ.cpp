//
// Created by titi on 18/03/17.
//

#include "MuslimPNJ.h"

MuslimPNJ::MuslimPNJ(int direction) : PNJ(direction) {
    healthPoints = PNJ_MUSLIM_STARTING_HEALTHPOINTS;
    damage = PNJ_MUSLIM_DAMAGE;
    value = PNJ_MUSLIM_VALUE;
}
MuslimPNJ::MuslimPNJ(Position position, int healthPoints, int direction)
        : PNJ(position, healthPoints, direction) {}

MuslimPNJ::MuslimPNJ(const Position &position, int healthPoints, const Position &last_pos, int direction)
        : PNJ(position, healthPoints, last_pos, direction) {}




