#ifndef MAP_HPP
#define MAP_HPP

#define SIZE 31 //Not > 41 because it's too big for a screen

#define GRASS "◼  "
#define PATH "   "
#define LIMIT "\033[34m◼\033[0m  "
#define TOWER "\033[31m◼\033[0m  "
#define NPC "\033[33m◼\033[0m  "

#define GRASS_INT -1
#define PATH_INT 0
#define LIMIT_INT -2
#define NPC_INT -3
#define TOWER_INT 1

#include <string>
#include <vector>
#include "Position.hpp"

class Map {
private:
    int matrix[SIZE][SIZE];
    const unsigned int _seed;
public:
    unsigned int get_seed() const;

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
    void display();
    bool isPath(Position pos);
    bool addTower(Position pos, int typeOfTower);
    bool removeTower(Position pos);
    bool addNPC(Position pos);
    bool removeNPC(Position pos);
    bool moveNPC(Position origin, Position nextPos);
};

#endif
