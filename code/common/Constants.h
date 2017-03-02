#ifndef PROJET_CONSTANTS_H
#define PROJET_CONSTANTS_H

#include <string>

static const int NORTH = 0;
static const int EAST = 1;
static const int SOUTH = 2;
static const int WEST = 3;
static const int DIRECTIONS[] = {NORTH, EAST, SOUTH, WEST};
static const std::string QUADRANT_NAMES[4] = {"NORTH", "EAST", "SOUTH", "WEST"};

const static int PARTNERS[4] = {EAST, NORTH, WEST, SOUTH};


static const int PNJ_STARTING_HEALTHPOINTS= 100;
static const int PNJ_STARTING_MOVESPEED = 100;

static const int  PLAYER_STARTING_HP =  100;
static const int  PLAYER_STARTING_MONEY = 200;

static const int PNJ_VALUE = 10;
static const int PNJ_DAMAGE= 10;

static const char PLACING_TOWER[2] = "t";
static const char WAVE[2] = "w";

static const int GOLD_EARNED_BY_TICK= 1;

static const float PERCENTAGE_RECOVERED_MONEY= (const float) (50 / 100.0);

const int GUN_TOWER_PRICE = 50;
const int GUN_TOWER_RANGE = 4;
const int GUN_TOWER_DAMAGE = 20;

#endif //PROJET_CONSTANTS_H
