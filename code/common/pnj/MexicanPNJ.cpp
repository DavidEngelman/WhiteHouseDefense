//
// Created by titi on 20/03/17.
//

#include "MexicanPNJ.h"

MexicanPNJ::MexicanPNJ(int direction) : PNJ(direction) {
    healthPoints = MEXICAN_PNJ_STARTING_HEALTHPOINTS;
    damage = MEXICAN_PNJ_DAMAGE;
    value = MEXICAN_PNJ_VALUE;
    typeOfPNJ = MEXICAN_PNJ_STR;
}

MexicanPNJ::MexicanPNJ(Position position, int healthPoints, int direction)
        : PNJ(position, healthPoints, direction) {}

MexicanPNJ::MexicanPNJ(const Position &position, int healthPoints, const Position &last_pos, int direction)
        : PNJ(position, healthPoints, last_pos, direction) {}