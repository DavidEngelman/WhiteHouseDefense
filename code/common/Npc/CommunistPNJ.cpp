#include "CommunistPNJ.h"

CommunistPNJ::CommunistPNJ(int direction) : PNJ(direction) {
    healthPoints = COMMUNIST_PNJ_STARTING_HEALTHPOINTS;
    damage = COMMUNIST_PNJ_DAMAGE;
    value = COMMUNIST_PNJ_VALUE;
    typeOfPNJ = COMMUNIST_PNJ_STR;
}

// Constructor used when unserializing
CommunistPNJ::CommunistPNJ(Position transitionPosition, int healthPoints, int direction, int isFrozen)
        : PNJ(transitionPosition, healthPoints, direction, isFrozen) { typeOfPNJ = COMMUNIST_PNJ_STR; }
