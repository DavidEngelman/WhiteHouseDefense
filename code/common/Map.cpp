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
    else if (seed == 1) initMapFromFile("../../maps/map2.map");
    else if (seed == 2) initMapFromFile("../../maps/map3.map");
    else {
        srand(seed);
        generateRandomMatrix();
    }
}

/*
 * Display the map on the screen using the gameState for drawing the towers and the pnjs
 */
void Map::display(GameState &gameState, int quadrant) {
    std::vector<AbstractTower *> &towers = gameState.getTowers();
    std::vector<Wave> &waves = gameState.getWaves();
    std::string &mode = gameState.getMode();

    system("clear");
    std::cout << "\t";
    for (int x = 0; x < SIZE; x++) {
        std::cout << x << " ";
        if (x < 10) std::cout << " ";
    }
    std::cout << std::endl;

    std::string typeOfTower;
    std::string typeOfPNJ;
    for (int y = 0; y < SIZE; y++) {
        std::cout << y << "\t";
        for (int x = 0; x < SIZE; x++) {
            switch (matrix[x][y]) {
                case TREE_INT:
                    std::cout << TREE;
                    break;

                case PINE_INT: // Simulate an 'or' statement
                case PINE_SNOW_INT:
                    std::cout << PINE;
                    break;

                case PALMER_INT:
                    std::cout << PALMER;
                    break;

                case GRASS_INT:
                case SAND_INT:
                case SNOW_INT:
                case DIRT_INT:
                case STONE_INT:
                    typeOfTower = "";
                    for (auto &tower : towers) {
                        Position pos = tower->getPosition();
                        if (x == pos.getX() && y == pos.getY()) {
                            typeOfTower = tower->getType();
                            break;
                        }
                    }
                    if (typeOfTower == GUN_TOWER_STR) std::cout << GUN_TOWER_CHAR;
                    else if (typeOfTower == SNIPER_TOWER_STR) std::cout << SNIPER_TOWER_CHAR;
                    else if (typeOfTower == SHOCK_TOWER_STR) std::cout << SHOCK_TOWER_CHAR;
                    else std::cout << GRASS;
                    break;

                case PATH_INT:
                    typeOfPNJ = "";
                    for (auto &wave : waves) {
                        std::vector<PNJ*> &pnjs = wave.getPnjs();
                        for (auto &pnj : pnjs) {
                            Position pos = pnj->getPosition();
                            if (x == pos.getX() && y == pos.getY()) {
                                typeOfPNJ = pnj->getType();
                                break;
                            }
                        }
                        if (typeOfPNJ != "") break;
                    }
                    if (typeOfPNJ == MEXICAN_PNJ_STR) std::cout << MEXICAN_PNJ_CHAR;
                    else if (typeOfPNJ == COMMUNIST_PNJ_STR) std::cout << COMMUNIST_PNJ_CHAR;
                    else if (typeOfPNJ == MUSLIM_PNJ_STR) std::cout << MUSLIM_PNJ_CHAR;
                    else std::cout << PATH;
                    break;

                case BASE_INT:
                    if (computeQuadrant(Position(x, y)) == quadrant) {
                        std::cout << GREEN_BASE;
                    } else {

                        if ((mode == TEAM_MODE) && (PARTNERS[computeQuadrant(Position(x, y))] == quadrant)) {
                            std::cout << PURPLE_BASE;
                        } else {
                            std::cout << BASE;
                        }
                    }
                    break;

                case WATER_ROCK_INT:
                case SAND_ROCK_INT:
                case GRASS_ROCK_INT:
                case DIRT_ROCK_INT:
                    std::cout << ROCK;
                    break;

                case WATER_INT:
                case LAVA_INT:
                    std::cout << WATER;
                    break;

                case SAND_STONE_INT:
                    std::cout << MUD;
                    break;

                default:
                    std::cout << UNKNOWN;
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
                matrix[x][y] = PATH_INT;
            } else if (y == SIZE / 2 and SIZE / 2 - 2 <= x and x <= SIZE / 2 + 2) {
                matrix[x][y] = PATH_INT;
            } else if (x == y or x + y == SIZE - 1) {
                matrix[x][y] = GRASS_ROCK_INT;
            } else {
                matrix[x][y] = GRASS_INT;
            }
        }
    }
}

/*
 * Generate a random path on the up quarter
 */
void Map::generateQuarterMap(Position end) {
    if (end.getY() == 0) {
        matrix[end.getX()][end.getY()] = BASE_INT;
        return;
    }

    std::vector<Position> possibleWays;

    Position nextToEnd(end.getX(), end.getY() - 1);
    if (matrix[nextToEnd.getX()][nextToEnd.getY()] != GRASS_ROCK_INT && !isNextToPath(nextToEnd))
        possibleWays.push_back(nextToEnd);

    nextToEnd.setY(end.getY());
    nextToEnd.setX(end.getX() - 1);
    if (matrix[nextToEnd.getX()][nextToEnd.getY()] != GRASS_ROCK_INT && !isNextToPath(nextToEnd))
        possibleWays.push_back(nextToEnd);

    nextToEnd.setX(end.getX() + 1);
    if (matrix[nextToEnd.getX()][nextToEnd.getY()] != GRASS_ROCK_INT && !isNextToPath(nextToEnd))
        possibleWays.push_back(nextToEnd);

    unsigned int way = (unsigned int) (rand() % possibleWays.size());

    matrix[possibleWays[way].getX()][possibleWays[way].getY()] = PATH_INT;
    generateQuarterMap(possibleWays[way]);
}

/*
 * Return true if the cell of the matrix is next to more than 1 path cell
 */
bool Map::isNextToPath(Position pos) {
    int count = 0;
    if (matrix[pos.getX() + 1][pos.getY()] == PATH_INT) count++;
    if (pos.getY() > 0 && matrix[pos.getX() - 1][pos.getY()] == PATH_INT) count++;
    if (matrix[pos.getX()][pos.getY() + 1] == PATH_INT) count++;
    if (matrix[pos.getX()][pos.getY() - 1] == PATH_INT) count++;
    return count > 1;
}

/*
 * Copy the path of the up quarter to the three other quarters
 */
void Map::copyQuarter() {
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (y < x and x + y < SIZE) {
                matrix[y][SIZE - 1 - x] = matrix[x][y];
                matrix[SIZE - 1 - x][SIZE - 1 - y] = matrix[x][y];
                matrix[SIZE - 1 - y][x] = matrix[x][y];
            }
        }
    }
}

bool Map::isPath(Position pos) const {
    return matrix[pos.getX()][pos.getY()] == PATH_INT;
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
    int cell = matrix[pos.getX()][pos.getY()];

    return cell == GRASS_ROCK_INT or cell == TREE_INT or cell == PINE_INT
        or cell == PALMER_INT or cell == WATER_INT or cell == SAND_STONE_INT
        or cell == WATER_ROCK_INT or cell == SAND_ROCK_INT or cell == LAVA_INT
        or cell == PINE_SNOW_INT or cell == DIRT_ROCK_INT;
}

void Map::initMapFromFile(std::string filename) {
    std::ifstream file(filename, std::ios::in);
    char c;
    std::string number = "";
    int x = 0;
    int y = 0;
    while (file >> c) {
        if (c != ',') {
            number += c;
        } else {
            matrix[x][y] = stoi(number);
            number = "";

            x++;
            if (x == SIZE) {
                x = 0;
                y++;
            }
        }
    }
}

bool Map::isBase(Position pos) const {
    return matrix[pos.getX()][pos.getY()] == BASE_INT;
}

