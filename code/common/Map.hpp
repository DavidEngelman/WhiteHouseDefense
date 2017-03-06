#ifndef MAP_HPP
#define MAP_HPP

const int SIZE = 31; //Not > 41 because it's too big for a screen

#define GRASS "◼  "
#define GREEN_GRASS "\033[32m◼\033[0m  "
#define PURPLE_GRASS "\033[35m◼\033[0m  "

#define PATH "   "
#define LIMIT "\033[34m◼\033[0m  "
#define NPC "\033[33m☪\033[0m  "
#define BASE "\033[31m✈\033[0m  "

#define PATH_INT 0
#define GRASS_INT -1
#define LIMIT_INT -2

// Tiles
#define CROSS 0
#define UP_DOWN 1
#define LEFT_RIGHT 2
#define LEFT_DOWN 3
#define LEFT_UP 4
#define UP_RIGHT 5
#define DOWN_RIGHT 6
#define CASTLE 7

#include <string>
#include <vector>
#include "Position.hpp"
#include "GameState.hpp"
#include "Constants.h"

class GameState;

/*
 * This class's matrix represents the terrain, the background of the map.
 * It keeps track of which parts of the terrain are path, which are grass and which
 * are the delimiters between the quadrants.
 *
 * Important: the matrix is constant. It is the background/terrain, independently of towers or NPCs.
 *
 * When we want to show the map (with towers and NPCs) to the user, we draw it dynamically from the
 * map matrix (the terrain, the background) and the gameState (which contains the changing parts of the game:
 * the towers and NPCs).
 */

class Map {
private:
    int matrix[SIZE][SIZE];
    int tileMatrix[SIZE][SIZE];

    void generateRandomMatrix();
    void initMap();
    void generateQuarterMap(Position position);
    const bool isNextToPath(Position position);
    void copyQuarter();
    void generateTiles();
    int computeTile(Position pos);

public:
    Map(unsigned seed);
    const void display(GameState& gameState, int quadrant) const;
    const bool isPath(Position pos) const;
    bool isDelimiter(Position pos) const;
    static const int computeQuadrant(Position pos);
};

#endif
