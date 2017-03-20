//
// Created by titi on 20/03/17.
//

#include "MexicanPNJ.h"

MexicanPNJ::MexicanPNJ(int direction) : PNJ(direction) {
    healthPoints = PNJ_MEXICAN_STARTING_HEALTHPOINTS;
    damage = PNJ_MEXICAN_DAMAGE;
    value = PNJ_MEXICAN_VALUE;
}

MexicanPNJ::MexicanPNJ(Position position, int healthPoints, int direction)
        : PNJ(position, healthPoints, direction) {}

MexicanPNJ::MexicanPNJ(const Position &position, int healthPoints, const Position &last_pos, int direction)
        : PNJ(position, healthPoints, last_pos, direction) {}