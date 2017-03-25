#include "MuslimPNJ.h"

MuslimPNJ::MuslimPNJ(int direction) : PNJ(direction) {
    healthPoints = MUSLIM_PNJ_STARTING_HEALTHPOINTS;
    damage = MUSLIM_PNJ_DAMAGE;
    value = MUSLIM_PNJ_VALUE;
    typeOfPNJ = MUSLIM_PNJ_STR;
}

// Constructor used when unserializing
MuslimPNJ::MuslimPNJ(Position transitionPosition, int healthPoints, int direction)
        : PNJ(transitionPosition, healthPoints, direction) { typeOfPNJ = MUSLIM_PNJ_STR; }





