//
// Created by titi on 20/03/17.
//

#include "CommunistPNJ.h"

CommunistPNJ::CommunistPNJ(int direction) : PNJ(direction) {
    healthPoints = COMMUNIST_PNJ_STARTING_HEALTHPOINTS;
    damage = COMMUNIST_PNJ_DAMAGE;
    value = COMMUNIST_PNJ_VALUE;
    typeOfPNJ = COMMUNIST_PNJ_STR;
}

CommunistPNJ::CommunistPNJ(Position position, int healthPoints, int direction)
        : PNJ(position, healthPoints, direction) {}

CommunistPNJ::CommunistPNJ(const Position &position, int healthPoints, const Position &last_pos, int direction)
        : PNJ(position, healthPoints, last_pos, direction) {}