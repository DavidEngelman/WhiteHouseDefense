#ifndef MAP_HPP
#define MAP_HPP

const int SIZE = 41;

#define GRASS "◼  "
#define UNKNOWN "?  "
#define PATH "   "
#define MUD "☒  "
#define ROCK "\033[34m⛰\033[0m  "
#define BASE "\033[31m✈\033[0m  "
#define GREEN_BASE "\033[32m✈\033[0m  "
#define PURPLE_BASE "\033[35m✈\033[0m  "
#define TREE "\033[32m☘\033[0m  "
#define PINE "\033[32m△\033[0m  "
#define PALMER "\033[32m⸙\033[0m  "
#define WATER "\033[34m~\033[0m  "

#define PATH_INT 0
#define GRASS_INT 1
#define BASE_INT 2
#define GRASS_ROCK_INT 3
#define TREE_INT 4
#define PINE_INT 5
#define SAND_INT 6
#define PALMER_INT 7
#define WATER_INT 8
#define SAND_STONE_INT 9
#define SAND_ROCK_INT 10
#define WATER_ROCK_INT 11
#define LAVA_INT 12
#define SNOW_INT 13
#define PINE_SNOW_INT 14
#define DIRT_INT 15
#define DIRT_ROCK_INT 16
#define STONE_INT 17

#include <string>
#include <vector>
#include "Position.hpp"
#include "gamestate/GameState.hpp"
#include "Constants.hpp"

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
    virtual void display(GameState& gameState, int quadrant);
    bool isPath(Position pos) const;
    bool isObstacle(Position pos) const;
    bool isBase(Position pos) const;
    static int computeQuadrant(Position pos);

    virtual Position getHighlightedPosition() const { return Position(-1, -1); }

};

#endif
