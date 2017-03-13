#include "Map.hpp"
#include <fstream>
#include <iostream>
#include <ctime>

/*
 * Constructor used to build the same map for the server and all the clients
 * because the server send the seed to all the players instead of sending the entire map
 */

Map::Map(unsigned seed) {
    if (seed == 0) initMapFromFile("../../maps/map1.map");
    else {
        srand(seed);
        generateRandomMatrix();
    }
}

/*
 * Display the map on the screen using the gameState for drawing the towers and the pnjs
 */
void Map::display(GameState &gameState, int quadrant) const {
    std::vector<AbstractTower *> &towers = gameState.getTowers();
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
                case TREE_INT:
                    std::cout << TREE;
                    break;
                case PINE_INT:
                    std::cout << PINE;
                    break;
                case GRASS_INT:
                    typeOfTower = "";
                    for (auto &tower : towers) {
                        Position pos = tower->getPosition();
                        if (x == pos.getX() && y == pos.getY()) {
                            typeOfTower = tower->getType();
                            break;
                        }
                    }
                    if (typeOfTower == GUN_TOWER_STR) {
                        std::cout << GUN_TOWER_CHAR;
                    } else if (typeOfTower == SNIPER_TOWER_STR) {
                        std::cout << SNIPER_TOWER_CHAR;
                    } else if (typeOfTower == SHOCK_TOWER_STR) {
                        std::cout << SHOCK_TOWER_CHAR;
                    } else {

                        if (computeQuadrant(Position(x, y)) == quadrant) {
                            std::cout << GREEN_GRASS;
                        } else {

                            if ((mode == TEAM_MODE) && (PARTNERS[computeQuadrant(Position(x, y))] == quadrant)) {
                                std::cout << PURPLE_GRASS;
                            } else {
                                std::cout << GRASS;
                            }
                        }
                    }

                    break;
                case PATH_INT:
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
                    break;
                case BASE_INT:
                    std::cout << BASE;
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
    Position begin(SIZE / 2, SIZE / 2 - 2);
    generateQuarterMap(begin);
    copyQuarter();
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
            if (x == SIZE / 2 and SIZE / 2 - 2 <= y and y <= SIZE / 2 + 2) {
                matrix[y][x] = PATH_INT;
            } else if (y == SIZE / 2 and SIZE / 2 - 2 <= x and x <= SIZE / 2 + 2) {
                matrix[y][x] = PATH_INT;
            } else if (x == y or x + y == SIZE - 1) {
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
        matrix[end.getY()][end.getX()] = BASE_INT;
        return;
    }

    std::vector<Position> possibleWays;

    Position nextToEnd(end.getX(), end.getY() - 1);
    if (matrix[nextToEnd.getY()][nextToEnd.getX()] != LIMIT_INT && !isNextToPath(nextToEnd))
        possibleWays.push_back(nextToEnd);

    nextToEnd.setY(end.getY());
    nextToEnd.setX(end.getX() - 1);
    if (matrix[nextToEnd.getY()][nextToEnd.getX()] != LIMIT_INT && !isNextToPath(nextToEnd))
        possibleWays.push_back(nextToEnd);

    nextToEnd.setX(end.getX() + 1);
    if (matrix[nextToEnd.getY()][nextToEnd.getX()] != LIMIT_INT && !isNextToPath(nextToEnd))
        possibleWays.push_back(nextToEnd);

    unsigned int way = (unsigned int) (rand() % possibleWays.size());

    matrix[possibleWays[way].getY()][possibleWays[way].getX()] = PATH_INT;
    generateQuarterMap(possibleWays[way]);
}

/*
 * Return true if the cell of the matrix is next to more than 1 path cell
 */
bool Map::isNextToPath(Position pos) {
    int count = 0;
    if (matrix[pos.getY() + 1][pos.getX()] == PATH_INT) count++;
    if (pos.getY() > 0 && matrix[pos.getY() - 1][pos.getX()] == PATH_INT) count++;
    if (matrix[pos.getY()][pos.getX() + 1] == PATH_INT) count++;
    if (matrix[pos.getY()][pos.getX() - 1] == PATH_INT) count++;
    return count > 1;
}

/*
 * Copy the path of the up quarter to the three other quarters
 */
void Map::copyQuarter() {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (y < x and x + y < SIZE) {
                matrix[x][SIZE - 1 - y] = matrix[y][x];
                matrix[SIZE - 1 - y][SIZE - 1 - x] = matrix[y][x];
                matrix[SIZE - 1 - x][y] = matrix[y][x];
            }
        }
    }
}

bool Map::isPath(Position pos) const {
    return matrix[pos.getY()][pos.getX()] == PATH_INT;
}

/*
 * This function return in which quadrant is the Position pos
 */
int Map::computeQuadrant(Position pos) {
    // The origin of the map is in the upper-left corner
    // The growing diagonal is : y = -x + size-1,
    // The decreasing diagonal is : y = x
    bool aboveGrowingDiagonal = pos.getX() + pos.getY() < SIZE - 1;
    bool aboveDecreasingDiagonal = pos.getX() > pos.getY();

    if (aboveGrowingDiagonal && aboveDecreasingDiagonal) {
        return NORTH;
    } else if (!aboveGrowingDiagonal && !aboveDecreasingDiagonal) {
        return SOUTH;
    } else if (aboveGrowingDiagonal && !aboveDecreasingDiagonal) {
        return WEST;
    } else {
        return EAST;
    }
}

bool Map::isObstacle(Position pos) const {
    int cell = matrix[pos.getY()][pos.getX()];

    return (cell == LIMIT_INT or cell == TREE_INT or cell == PINE_INT);
}

void Map::initMapFromFile(std::string filename) {
    std::ifstream file(filename, std::ios::in);
    char c;
    int x = 0;
    int y = 0;
    while (file >> c) {
        if (c != ',') {
            switch (c) {
                case '0':
                    matrix[y][x] = PATH_INT;
                    break;
                case '1':
                    matrix[y][x] = GRASS_INT;
                    break;
                case '2':
                    matrix[y][x] = BASE_INT;
                    break;
                case '3':
                    matrix[y][x] = LIMIT_INT;
                    break;
                case '4':
                    matrix[y][x] = TREE_INT;
                    break;
                default:
                    matrix[y][x] = PINE_INT;
                    break;
            }

            x++;
            if (x == SIZE) {
                x = 0;
                y++;
            }
        }
    }
}

