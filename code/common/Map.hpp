#ifndef MAP_HPP
#define MAP_HPP

#define SIZE 31 //Not > 41 because it's too big for a screen

#define GRASS "◼  "
#define GREEN_GRASS "\033[32m◼\033[0m  "
#define PATH "   "
#define LIMIT "\033[34m◼\033[0m  "
#define TOWER "\033[31m♜\033[0m  "
#define NPC "\033[33m☪\033[0m  "
#define BASE "\033[31m✈\033[0m  "

#define PATH_INT 0
#define GRASS_INT -1
#define LIMIT_INT -2

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
 * When we want to show the map (with towers and NPCs) to the user, we draw it dynamically from the
 * map matrix (the terrain, the background) and the gameState (which contains the changing parts of the game:
 * the towers and NPCs).
 */

class Map {
private:
    int matrix[SIZE][SIZE];

private:

    void generateRandomMatrix();
    void initMap();
    void generateQuarterMap(Position position);
    const bool isNextToPath(Position position);
    void copyQuarter();

public:
    Map(unsigned seed);
    const void display(GameState& gameState, int quadrant) const;
    const bool isPath(Position pos) const;
    static const int computeQuadrant(Position pos);
};

#endif
