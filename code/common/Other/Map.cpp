#include "Map.hpp"
#include <fstream>
#include <iostream>
#include <ctime>
#include <cassert>

/*
 * Constructor used to build the same map for the server and all the clients
 * because the server send the seed to all the players instead of sending the entire map
 */

Map::Map(unsigned seed) {
    std::string filename = "../../maps/map" + std::to_string(seed+1) + ".map";
    initMapFromFile(filename);
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
                    else if (typeOfTower == MISSILE_TOWER_STR) std::cout << MISSILE_TOWER_CHAR;
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

bool Map::isPath(Position pos) const {
    assert(0 <= pos.getX() <= SIZE);
    assert(0 <= pos.getY() <= SIZE);
    return matrix[pos.getX()][pos.getY()] == PATH_INT;
}

/*
 * This function return in which quadrant is the Position pos
 */
int Map::computeQuadrant(Position pos) {
    assert(0 <= pos.getX() <= SIZE);
    assert(0 <= pos.getY() <= SIZE);
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
    assert(0 <= pos.getX() <= SIZE);
    assert(0 <= pos.getY() <= SIZE);
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
    assert(0 <= pos.getX() <= SIZE);
    assert(0 <= pos.getY() <= SIZE);
    return matrix[pos.getX()][pos.getY()] == BASE_INT;
}


