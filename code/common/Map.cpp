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
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            switch (matrix[y][x]) {
                case -1:
                    std::cout << GRASS;
                    break;
                case 0:
                    std::cout << PATH;
                    break;
                case -2:
                    std::cout << LIMIT;
                    break;
                case -3:
                    std::cout << PNG;
                    break;
                default:
                    std::cout << TOWER;
                    break;
            }
        }
        std::cout << std::endl;
    }
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
                matrix[y][x] = 0;
            } else if (y == SIZE/2 and SIZE/2-2 <= x and x <= SIZE/2+2) {
                matrix[y][x] = 0;
            } else if (x == y or x + y == SIZE-1) {
                matrix[y][x] = -2;
            } else {
                matrix[y][x] = -1;
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
    if (matrix[nextToEnd.y][nextToEnd.x] != -2 && !isNextToPath(nextToEnd)) possibleWays.push_back(nextToEnd);
    nextToEnd.y = end.y;
    nextToEnd.x = end.x-1;
    if (matrix[nextToEnd.y][nextToEnd.x] != -2 && !isNextToPath(nextToEnd)) possibleWays.push_back(nextToEnd);
    nextToEnd.x = end.x+1;
    if (matrix[nextToEnd.y][nextToEnd.x] != -2 && !isNextToPath(nextToEnd)) possibleWays.push_back(nextToEnd);

    unsigned int way = (unsigned int) (rand() % possibleWays.size());

    int save = matrix[possibleWays[way].y][possibleWays[way].x];
    matrix[possibleWays[way].y][possibleWays[way].x] = 0;
    if (generateQuarterMap(possibleWays[way])) return true;
    matrix[possibleWays[way].y][possibleWays[way].x] = save;
    return false;
}

bool Map::isNextToPath(Position position) {
    int count = 0;
    if (matrix[position.y+1][position.x] == 0) count++;
    if (position.y > 0 && matrix[position.y-1][position.x] == 0) count++;
    if (matrix[position.y][position.x+1] == 0) count++;
    if (matrix[position.y][position.x-1] == 0) count++;
    return count >= 2;
}

bool Map::addTower(int x, int y, int typeOfTower) {
    if (matrix[y][x] == -1) {
        matrix[y][x] = typeOfTower*10; // 10 = number of upgrades per tower possible
        return true;
    }
    return false;
}

bool Map::removeTower(int x, int y) {
    if (matrix[y][x] > 0) {
        matrix[y][x] = -1;
        return true;
    }
    return false;
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
                matrix[y][x] = 0;
            } else if (y == SIZE/2 and 0 <= x and x < SIZE) {
                matrix[y][x] = 0;
            } else if (x == y or x + y == SIZE-1) {
                matrix[y][x] = -2;
            } else {
                matrix[y][x] = -1;
            }
        }
    }
}
