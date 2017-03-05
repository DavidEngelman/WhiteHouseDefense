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

// Constant of the towers
const int GUN_TOWER_PRICE = 50;
const int GUN_TOWER_RANGE = 4;
const int GUN_TOWER_DAMAGE = 20;

const int SNIPER_TOWER_PRICE = 100;
const int SNIPER_TOWER_RANGE = 10;
const int SNIPER_TOWER_DAMAGE = 10;

const int SHOCK_TOWER_PRICE = 150;
const int SHOCK_TOWER_RANGE = 3;
const int SHOCK_TOWER_DAMAGE = 5;

static const int STEP_DURATION_IN_MS = 1000;
static const int INITIAL_NUMBER_OF_PNJS_PER_WAVE = 5;
static const int TIMED_GAME_DURATION = 120;

static const int NUM_PLAYERS = 4;
static const int NUM_SECONDS_TO_PLACE_TOWER = 20;
static const int INTERVAL_BETWEEN_SENDS_IN_MS = 200;
static const int INTERVAL_BETWEEN_PNJS_IN_WAVE_IN_MS = 1000;

#endif //PROJET_CONSTANTS_H
