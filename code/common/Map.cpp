#include "Map.hpp"
#include <fstream>
#include <iostream>
#include <ctime>

Map::Map() {
    srand((unsigned)time(0));
    generateRandomMatrix();
}

Map::Map(unsigned seed) {
    if (seed == 0) basicMap();
    else {
        srand(seed);
        generateRandomMatrix();
    }
}

void Map::display() {
    std::cout << std::string(50, '\n');

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
                    std::cout << GRASS;
                    break;
                case PATH_INT:
                    std::cout << PATH;
                    break;
                case LIMIT_INT:
                    std::cout << LIMIT;
                    break;
                case PNG_INT:
                    std::cout << PNG;
                    break;
                default:
                    std::cout << TOWER;
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
    if (end.y == 0) {
        return true;
    }

    std::vector<Position> possibleWays;
    Position nextToEnd(end.x, end.y-1);
    std::cout << matrix[nextToEnd.y][nextToEnd.x] << std::endl;
    if (matrix[nextToEnd.y][nextToEnd.x] != LIMIT_INT && !isNextToPath(nextToEnd)) possibleWays.push_back(nextToEnd);
    nextToEnd.y = end.y;
    nextToEnd.x = end.x-1;
    if (matrix[nextToEnd.y][nextToEnd.x] != LIMIT_INT && !isNextToPath(nextToEnd)) possibleWays.push_back(nextToEnd);
    nextToEnd.x = end.x+1;
    if (matrix[nextToEnd.y][nextToEnd.x] != LIMIT_INT && !isNextToPath(nextToEnd)) possibleWays.push_back(nextToEnd);

    unsigned int way = (unsigned int) (rand() % possibleWays.size());

    int save = matrix[possibleWays[way].y][possibleWays[way].x];
    matrix[possibleWays[way].y][possibleWays[way].x] = PATH_INT;
    if (generateQuarterMap(possibleWays[way])) return true;
    matrix[possibleWays[way].y][possibleWays[way].x] = save;
    return false;
}

bool Map::isNextToPath(Position position) {
    int count = 0;
    if (matrix[position.y+1][position.x] == PATH_INT) count++;
    if (position.y > 0 && matrix[position.y-1][position.x] == PATH_INT) count++;
    if (matrix[position.y][position.x+1] == PATH_INT) count++;
    if (matrix[position.y][position.x-1] == PATH_INT) count++;
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
    return matrix[pos.y][pos.x] == PATH_INT;
}

bool Map::addTower(Position pos, int typeOfTower) {
    if (matrix[pos.y][pos.x] == GRASS_INT) {
        matrix[pos.y][pos.x] = typeOfTower*10+TOWER_INT; // 10 = number of upgrades per tower possible
        return true;
    }
    return false;
}

bool Map::removeTower(Position pos) {
    if (matrix[pos.y][pos.x] >= TOWER_INT) {
        matrix[pos.y][pos.x] = GRASS_INT;
        return true;
    }
    return false;
}

bool Map::addPNG(Position pos) {
    return false;
}

bool Map::removePNG(Position pos) {
    return false;
}

bool Map::movePNG(Position origin, Position nextPos) {
    return false;
}