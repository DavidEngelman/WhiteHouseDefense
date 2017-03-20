//
// Created by titi on 20/03/17.
//

#include "CommunistPNJ.h"

CommunistPNJ::CommunistPNJ(int direction) : PNJ(direction) {
    healthPoints = PNJ_COMMUNIST_STARTING_HEALTHPOINTS;
    damage = PNJ_COMMUNIST_DAMAGE;
    value = PNJ_COMMUNIST_VALUE;
}

CommunistPNJ::CommunistPNJ(Position position, int healthPoints, int direction)
        : PNJ(position, healthPoints, direction) {}

CommunistPNJ::CommunistPNJ(const Position &position, int healthPoints, const Position &last_pos, int direction)
        : PNJ(position, healthPoints, last_pos, direction) {}