#ifndef MAP_HPP
#define MAP_HPP

#define SIZE 31 //Not > 41 because it's too big for a screen

#define GRASS "◼  "
#define PATH "   "
#define LIMIT "\033[34m◼\033[0m  "
#define TOWER "\033[31m◼\033[0m  "
#define NPC "\033[33m◼\033[0m  "
#define BASE "\033[31m♜\033[0m  "

#define GRASS_INT -1
#define PATH_INT 0
#define LIMIT_INT -2
#define NPC_INT -3
#define TOWER_INT 1

#include <string>
#include <vector>
#include "Position.hpp"
#include "GameState.hpp"

class GameState;

/*
 * This class's matrix represents the terrain, the background of the map.
 * It keeps track of which parts of the terrain are path, which are grass and which
 * are the delimiters between the quadrants.
 *
 * Important: the matrix is constant. It is the background/terrain, independently of towers or NPCs.
 *
 * When we want to show the map (with towers and NPCs) to the user, we generate it dynamically from the
 * map matrix (the terrain, the background) and the gameState (which contains the changing parts of the game:
 * the towers and NPCs).
 */
class Map {
private:
    int matrix[SIZE][SIZE];

private:

    void generateRandomMatrix();
    void initMap();
    bool generateQuarterMap(Position position);
    bool isNextToPath(Position position);
    void copyQuarter();
    void basicMap();

public:
    Map();
    Map(unsigned seed);
    void display(GameState& gameState);
    bool isPath(Position pos);
};

#endif
