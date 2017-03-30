#ifndef MAP_HPP
#define MAP_HPP

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

#include <string>
#include <vector>
#include "Position.hpp"
#include "../Gamestate/GameState.hpp"
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

    void initMapFromFile(std::string filename);


public:
    Map(unsigned seed);
    virtual void display(GameState& gameState, int quadrant);
    bool isPath(const Position &pos) const;
    bool isObstacle(const Position &pos) const;
    bool isBase(const Position &pos) const;
    static int computeQuadrant(const Position &pos);

    virtual Position getHighlightedPosition() const { return Position(-1, -1); }

    virtual bool isEnemyBaseInHighlightedPosition(int quadrant) {return false;}
};

#endif
