#ifndef MAP_HPP
#define MAP_HPP

const int SIZE = 41;

#define GRASS "◼  "
#define GREEN_GRASS "\033[32m◼\033[0m  "
#define PURPLE_GRASS "\033[35m◼\033[0m  "

#define PATH "   "
#define LIMIT "\033[34m⛰\033[0m  "
#define NPC "\033[33m☪\033[0m  "
#define BASE "\033[31m✈\033[0m  "
#define TREE "\033[34m☘\033[0m  "
#define PINE "\033[34m△\033[0m  "

#define PATH_INT 0
#define GRASS_INT -1
#define LIMIT_INT -2
#define TREE_INT -3
#define PINE_INT -4

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
protected:
    int matrix[SIZE][SIZE];

    void generateRandomMatrix();
    void initMap();
    void generateQuarterMap(Position position);
    bool isNextToPath(Position position);
    void copyQuarter();
    void initMapFromFile(std::string filename);


public:
    Map(unsigned seed);
    virtual void display(GameState& gameState, int quadrant) const;
    bool isPath(Position pos) const;
    bool isDelimiter(Position pos) const;
    static int computeQuadrant(Position pos);

    bool isObstacle(Position pos) const;
};

#endif
