#include "Map.hpp"
#include <fstream>
#include <iostream>
#include <ctime>

Map::Map() {
    srand((unsigned) time(0));
    generateRandomMatrix();
}

Map::Map(unsigned seed) {
    if (seed == 0) basicMap();
    else {
        srand(seed);
        generateRandomMatrix();
    }
}

void Map::display(GameState& gameState) {
    std::vector<AbstractTower*> &towers = gameState.getTowers();
    std::vector<Wave> &waves = gameState.getWaves();
    system("clear");

    std::cout << "\t";
    for (int x = 0; x < SIZE; x++) {
        std::cout << x << " ";
        if (x < 10) std::cout << " ";
    }
    std::cout << std::endl;

    for (int y = 0; y < SIZE; y++) {
        std::cout << y << "\t";
        for (int x = 0; x < SIZE; x++) {
            switch (matrix[y][x]) {
                case GRASS_INT:
                    for (auto &tower : towers) {
                        Position pos = tower->getPosition();
                        if (x == pos.getX() && y == pos.getY()) std::cout << TOWER;
                        else std::cout << GRASS;
                    }
                    break;
                case PATH_INT:
                    if (x == 0 or y == 0 or x == SIZE-1 or y == SIZE-1) std::cout << BASE;
                    else {
                        for (auto &wave : waves) {
                            std::vector<PNJ> &pnjs = wave.getPnjs();
                            for (auto &pnj : pnjs) {
                                Position pos = pnj.getPosition();
                                if (x == pos.getX() && y == pos.getY()) std::cout << NPC;
                                else std::cout << PATH;
                            }
                        }
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
    initMap();
    Position begin(SIZE/2, SIZE/2-2);
    generateQuarterMap(begin);
    copyQuarter();
}

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

bool Map::generateQuarterMap(Position end) {
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

    int save = matrix[possibleWays[way].getY()][possibleWays[way].getX()];
    matrix[possibleWays[way].getY()][possibleWays[way].getX()] = PATH_INT;
    if (generateQuarterMap(possibleWays[way])) return true;
    matrix[possibleWays[way].getY()][possibleWays[way].getX()] = save;
    return false;
}

bool Map::isNextToPath(Position pos) {
    int count = 0;
    if (matrix[pos.getY()+1][pos.getX()] == PATH_INT) count++;
    if (pos.getY() > 0 && matrix[pos.getY()-1][pos.getX()] == PATH_INT) count++;
    if (matrix[pos.getY()][pos.getX()+1] == PATH_INT) count++;
    if (matrix[pos.getY()][pos.getX()-1] == PATH_INT) count++;
    return count >= 2;
}

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

void Map::basicMap() {
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

bool Map::isPath(Position pos) {
    return matrix[pos.getY()][pos.getX()] == PATH_INT;
}