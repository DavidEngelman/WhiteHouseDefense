#include "MexicanPNJ.h"

MexicanPNJ::MexicanPNJ(int direction) : PNJ(direction) {
    healthPoints = MEXICAN_PNJ_STARTING_HEALTHPOINTS;
    damage = MEXICAN_PNJ_DAMAGE;
    value = MEXICAN_PNJ_VALUE;
    typeOfPNJ = MEXICAN_PNJ_STR;
}

// Constructor used when unserializing
MexicanPNJ::MexicanPNJ(Position transitionPosition, int healthPoints, int direction, int isFrozen)
        : PNJ(transitionPosition, healthPoints, direction, isFrozen) { typeOfPNJ = MEXICAN_PNJ_STR;}
