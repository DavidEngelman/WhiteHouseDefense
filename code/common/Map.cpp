#include "Map.hpp"
#include <fstream>
#include <iostream>
#include <ctime>

Map::Map(unsigned seed) {
    /*
     * Constructor used to build the same map for the server and all the clients
     * because the server send the seed to all the players instead of sending the entire map
     */
    if (seed == 0) basicMap();
    else if (seed == 1) trumpMap();
    else {
        srand(seed);
        generateRandomMatrix();
    }
}

const void Map::display(GameState& gameState) {
    /*
     * Display the map on the screen using the gameState for drawing the towers and the pnjs
     */
    std::vector<AbstractTower*> &towers = gameState.getTowers();
    std::vector<Wave> &waves = gameState.getWaves();
    system("clear");

    std::cout << "\t";
    for (int x = 0; x < SIZE; x++) {
        std::cout << x << " ";
        if (x < 10) std::cout << " ";
    }
    std::cout << std::endl;

    bool has_tower;
    bool has_npc;
    for (int y = 0; y < SIZE; y++) {
        std::cout << y << "\t";
        for (int x = 0; x < SIZE; x++) {
            switch (matrix[y][x]) {
                case GRASS_INT:
                    has_tower = false;
                    for (auto &tower : towers) {
                        Position pos = tower->getPosition();
                        if (x == pos.getX() && y == pos.getY()) {
                            has_tower = true;
                            break;
                        }
                    }
                    if (has_tower){
                        std::cout << TOWER;
                    } else {
                        std::cout << GRASS;
                    }

                    break;
                case PATH_INT:
                    if (x == 0 or y == 0 or x == SIZE-1 or y == SIZE-1) std::cout << BASE;
                    else {
                        has_npc = false;
                        for (auto &wave : waves) {
                            std::vector<PNJ> &pnjs = wave.getPnjs();
                            for (auto &pnj : pnjs) {
                                Position pos = pnj.getPosition();
                                if (x == pos.getX() && y == pos.getY()) {
                                    has_npc = true;
                                    break;
                                }
                            }
                            if (has_npc) break;
                        }
                        if (has_npc) std::cout << NPC;
                        else std::cout << PATH;
                    }

                    break;
                default:
                    std::cout << LIMIT;
                    break;
            }
        }
        std::cout << y << std::endl;
    }

    std::cout << "\t";
    for (int x = 0; x < SIZE; x++) {
        std::cout << x << " ";
        if (x < 10) std::cout << " ";
    }
    std::cout << std::endl;
}

void Map::generateRandomMatrix() {
    /*
     * Generate a random map
     */
    initMap();
    Position begin(SIZE/2, SIZE/2-2);
    generateQuarterMap(begin);
    copyQuarter();
}

void Map::initMap() {
    /*
     * Generate the most basic map that is common to all maps :
     * - The two diagonals of the square are the LIMITS of the quarters
     * - A small cross of PATH at the middle of the square
     * - The rest is GRASS
     */
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (x == SIZE/2 and SIZE/2-2 <= y and y <= SIZE/2+2) {
                matrix[y][x] = PATH_INT;
            } else if (y == SIZE/2 and SIZE/2-2 <= x and x <= SIZE/2+2) {
                matrix[y][x] = PATH_INT;
            } else if (x == y or x + y == SIZE-1) {
                matrix[y][x] = LIMIT_INT;
            } else {
                matrix[y][x] = GRASS_INT;
            }
        }
    }
}

bool Map::generateQuarterMap(Position end) {
    /*
     * Generate a random path on the up quarter
     */
    if (end.getY() == 0) {
        return true;
    }

    std::vector<Position> possibleWays;
    Position nextToEnd(end.getX(), end.getY()-1);
    if (matrix[nextToEnd.getY()][nextToEnd.getX()] != LIMIT_INT && !isNextToPath(nextToEnd)) possibleWays.push_back(nextToEnd);
    nextToEnd.setY(end.getY());
    nextToEnd.setX(end.getX()-1);
    if (matrix[nextToEnd.getY()][nextToEnd.getX()] != LIMIT_INT && !isNextToPath(nextToEnd)) possibleWays.push_back(nextToEnd);
    nextToEnd.setX(end.getX()+1);
    if (matrix[nextToEnd.getY()][nextToEnd.getX()] != LIMIT_INT && !isNextToPath(nextToEnd)) possibleWays.push_back(nextToEnd);

    unsigned int way = (unsigned int) (rand() % possibleWays.size());

    // TODO : voir s'il n'y a pas des trucs inutiles dans cette fonction
    int save = matrix[possibleWays[way].getY()][possibleWays[way].getX()];
    matrix[possibleWays[way].getY()][possibleWays[way].getX()] = PATH_INT;
    if (generateQuarterMap(possibleWays[way])) return true;
    matrix[possibleWays[way].getY()][possibleWays[way].getX()] = save;
    return false;
}

const bool Map::isNextToPath(Position pos) {
    /*
     * Return true if the cell of the matrix is next to more than 1 path cell
     */
    int count = 0;
    if (matrix[pos.getY()+1][pos.getX()] == PATH_INT) count++;
    if (pos.getY() > 0 && matrix[pos.getY()-1][pos.getX()] == PATH_INT) count++;
    if (matrix[pos.getY()][pos.getX()+1] == PATH_INT) count++;
    if (matrix[pos.getY()][pos.getX()-1] == PATH_INT) count++;
    return count > 1;
}

void Map::copyQuarter() {
    /*
     * Copy the path of the up quarter to the three other quarters
     */
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (y < x and x+y < SIZE) {
                matrix[x][SIZE-1-y] = matrix[y][x];
                matrix[SIZE-1-y][SIZE-1-x] = matrix[y][x];
                matrix[SIZE-1-x][y] = matrix[y][x];
            }
        }
    }
}

void Map::basicMap() {
    /*
     * Draw the map in the shape of a simple cross
     */
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (x == SIZE/2 and 0 <= y and y < SIZE) {
                matrix[y][x] = PATH_INT;
            } else if (y == SIZE/2 and 0 <= x and x < SIZE) {
                matrix[y][x] = PATH_INT;
            } else if (x == y or x + y == SIZE-1) {
                matrix[y][x] = LIMIT_INT;
            } else {
                matrix[y][x] = GRASS_INT;
            }
        }
    }
}

const bool Map::isPath(Position pos) {
    return matrix[pos.getY()][pos.getX()] == PATH_INT;
}

void Map::trumpMap() {
    /*
     * Draw the map in the shape of the Swastika
     */
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (x == SIZE/2 and 1 <= y and y < SIZE-1) {
                matrix[y][x] = PATH_INT;
            } else if (y == SIZE/2 and 1 <= x and x < SIZE-1) {
                matrix[y][x] = PATH_INT;
            } else if (y == 1 and x >= SIZE/2 and x < SIZE-2) {
                matrix[y][x] = PATH_INT;
            } else if (y == 0 and x == SIZE-3) {
                matrix[y][x] = PATH_INT;
            } else if (y == SIZE-2 and x >= 2 and x < SIZE/2) {
                matrix[y][x] = PATH_INT;
            } else if (y == SIZE-1 and x == 2) {
                matrix[y][x] = PATH_INT;
            } else if (x == SIZE-2 and y >= SIZE/2 and y < SIZE-2) {
                matrix[y][x] = PATH_INT;
            } else if (x == SIZE-1 and y == SIZE-3) {
                matrix[y][x] = PATH_INT;
            } else if (x == 1 and y >= 2 and y < SIZE/2) {
                matrix[y][x] = PATH_INT;
            } else if (x == 0 and y == 2) {
                matrix[y][x] = PATH_INT;
            } else if (x == y or x + y == SIZE-1) {
                matrix[y][x] = LIMIT_INT;
            } else {
                matrix[y][x] = GRASS_INT;
            }
        }
    }
}

const int Map::computeQuadrant(Position pos) {
    int realY = SIZE - pos.getY();
    int realX = pos.getX();

    // La diagonale croissante est celle qui respecte y = x,
    // et la diagonale decroissante est celle qui respecte y = -x
    bool aboveGrowingDiagonal = realY > realX;
    bool aboveDecreasingDiagonal = realY > -realX;

    if (aboveGrowingDiagonal && aboveDecreasingDiagonal){
        return NORTH;
    } else if (!aboveGrowingDiagonal && !aboveDecreasingDiagonal){
        return SOUTH;
    } else if (aboveGrowingDiagonal && !aboveDecreasingDiagonal){
        return WEST;
    } else {
        return EAST;
    }
}
