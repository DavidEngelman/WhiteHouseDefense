#include "Map.hpp"
#include <fstream>
#include <iostream>
#include <ctime>

/*
 * Constructor used to build the same map for the server and all the clients
 * because the server send the seed to all the players instead of sending the entire map
 */

Map::Map(unsigned seed) {
    srand(seed);
    generateRandomMatrix();
}

/*
 * Display the map on the screen using the gameState for drawing the towers and the pnjs
 */
const void Map::display(GameState& gameState, int quadrant) const {
    std::vector<AbstractTower*> &towers = gameState.getTowers();
    std::vector<Wave> &waves = gameState.getWaves();
    std::string mode;

    mode = gameState.getMode();

    system("clear");
    std::cout << "\t";
    for (int x = 0; x < SIZE; x++) {
        std::cout << x << " ";
        if (x < 10) std::cout << " ";
    }
    std::cout << std::endl;

    std::string typeOfTower;
    bool has_npc;
    for (int y = 0; y < SIZE; y++) {
        std::cout << y << "\t";
        for (int x = 0; x < SIZE; x++) {
            switch (matrix[y][x]) {
                case GRASS_INT:
                    typeOfTower = "";
                    for (auto &tower : towers) {
                        Position pos = tower->getPosition();
                        if (x == pos.getX() && y == pos.getY()) {
                            typeOfTower = tower->getType();
                            break;
                        }
                    }
                    if (typeOfTower == GUN_TOWER_STR){
                        std::cout << GUN_TOWER_CHAR;
                    } else if (typeOfTower == SNIPER_TOWER_STR) {
                        std::cout << SNIPER_TOWER_CHAR;
                    } else if (typeOfTower == SHOCK_TOWER_STR) {
                        std::cout << SHOCK_TOWER_CHAR;
                    } else {

                        if (computeQuadrant(Position(x,y)) == quadrant) {
                            std::cout << GREEN_GRASS;
                        } else{

                            if ((mode == TEAM_MODE) && (PARTNERS[computeQuadrant(Position(x,y))] == quadrant)){
                                std::cout << PURPLE_GRASS;
                            } else{
                                std::cout << GRASS;
                            }
                        }
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

/*
 * Generate a random map
 */
void Map::generateRandomMatrix() {
    initMap();
    Position begin(SIZE/2, SIZE/2-2);
    generateQuarterMap(begin);
    copyQuarter();
    generateTiles();
}

/*
 * Generate the most basic map that is common to all maps :
 * - The two diagonals of the square are the LIMITS of the quarters
 * - A small cross of PATH at the middle of the square
 * - The rest is GRASS
 */
void Map::initMap() {
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

/*
 * Generate a random path on the up quarter
 */
void Map::generateQuarterMap(Position end) {
    if (end.getY() == 0) {
        return;
    }

    std::vector<Position> possibleWays;
    Position nextToEnd(end.getX(), end.getY()-1);
    if (matrix[nextToEnd.getY()][nextToEnd.getX()] != LIMIT_INT && !isNextToPath(nextToEnd))
        possibleWays.push_back(nextToEnd);
    nextToEnd.setY(end.getY());
    nextToEnd.setX(end.getX()-1);
    if (matrix[nextToEnd.getY()][nextToEnd.getX()] != LIMIT_INT && !isNextToPath(nextToEnd))
        possibleWays.push_back(nextToEnd);
    nextToEnd.setX(end.getX()+1);
    if (matrix[nextToEnd.getY()][nextToEnd.getX()] != LIMIT_INT && !isNextToPath(nextToEnd))
        possibleWays.push_back(nextToEnd);

    unsigned int way = (unsigned int) (rand() % possibleWays.size());

    matrix[possibleWays[way].getY()][possibleWays[way].getX()] = PATH_INT;
    generateQuarterMap(possibleWays[way]);
}

/*
 * Return true if the cell of the matrix is next to more than 1 path cell
 */
const bool Map::isNextToPath(Position pos) {
    int count = 0;
    if (matrix[pos.getY()+1][pos.getX()] == PATH_INT) count++;
    if (pos.getY() > 0 && matrix[pos.getY()-1][pos.getX()] == PATH_INT) count++;
    if (matrix[pos.getY()][pos.getX()+1] == PATH_INT) count++;
    if (matrix[pos.getY()][pos.getX()-1] == PATH_INT) count++;
    return count > 1;
}

/*
 * Copy the path of the up quarter to the three other quarters
 */
void Map::copyQuarter() {
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

const bool Map::isPath(Position pos) const {
    return matrix[pos.getY()][pos.getX()] == PATH_INT;
}

/*
 * This function return in which quadrant is the Position pos
 */
const int Map::computeQuadrant(Position pos) {
    // The origin of the map is in the upper-left corner
    // The growing diagonal is : y = -x + size-1,
    // The decreasing diagonal is : y = x
    bool aboveGrowingDiagonal = pos.getX()+pos.getY() < SIZE-1;
    bool aboveDecreasingDiagonal = pos.getX() > pos.getY();

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

bool Map::isDelimiter(Position pos) const {
    // The center is not a delimiter
    if ((pos.getX() == SIZE / 2) && (pos.getY() == SIZE / 2)) return false;
    return (pos.getX() == pos.getY()) || (pos.getX() == ((SIZE - 1) - pos.getY()));
}

void Map::generateTiles() {
    for (int x = 0; x < SIZE; x++){
        for (int y = 0; y < SIZE; y++) {
            if (x == 0 or x == SIZE-1 or y == 0 or y == SIZE-1) {
                tileMatrix[x][y] = matrix[y][x] == 0 ? CASTLE : matrix[y][x];
            } else {
                tileMatrix[x][y] = matrix[y][x] == 0 ? computeTile(Position(x, y)) : matrix[y][x];
            }
        }
    }
}

int Map::computeTile(Position pos) {
    if (pos.getX() == SIZE/2 and pos.getY() == SIZE/2) return CROSS;

    bool up =       matrix[pos.getY()-1][pos.getX()] == 0;
    bool down =     matrix[pos.getY()+1][pos.getX()] == 0;
    bool left =     matrix[pos.getY()][pos.getX()-1] == 0;
    bool right =    matrix[pos.getY()][pos.getX()+1] == 0;

    if (up and down) return UP_DOWN;
    else if (left and right) return LEFT_RIGHT;
    else if (left and down) return LEFT_DOWN;
    else if (left and up) return LEFT_UP;
    else if (up and right) return UP_RIGHT;
    else return DOWN_RIGHT;
}
