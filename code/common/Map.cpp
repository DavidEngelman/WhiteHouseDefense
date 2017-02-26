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

void Map::display() {
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
                    std::cout << GRASS;
                    break;
                case PATH_INT:
                    if (x == 0 or y == 0 or x == SIZE-1 or y == SIZE-1) std::cout << BASE;
                    else std::cout << PATH;
                    break;
                case LIMIT_INT:
                    std::cout << LIMIT;
                    break;
                case NPC_INT:
                    std::cout << NPC;
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

bool Map::addTower(Position pos) {
    if (matrix[pos.getY()][pos.getX()] == GRASS_INT) {
        matrix[pos.getY()][pos.getX()] = TOWER_INT; // 10 = number of upgrades per tower possible
        return true;
    }
    return false;
}

bool Map::removeTower(Position pos) {
    if (matrix[pos.getY()][pos.getX()] >= TOWER_INT) {
        matrix[pos.getY()][pos.getX()] = GRASS_INT;
        return true;
    }
    return false;
}

bool Map::addNPC(Position pos) {
    return false;
}

bool Map::removeNPC(Position pos) {
    return false;
}

bool Map::moveNPC(Position origin, Position nextPos) {
    return false;
}

void Map::update(GameState &gameState) {
    std::vector<AbstractTower *> &towers = gameState.getTowers();
    for (auto &tower : towers) {
        addTower(tower->getPosition());
    }

    std::vector<Wave> &waves = gameState.getWaves();
    for (auto &wave : waves) {
        std::vector<PNJ> &pnjs = wave.getPnjs();
        for (auto &pnj : pnjs) {
            addNPC(pnj.getPosition());
        }
    }
}


/*

void Map::add_tower(Position pos) {
    dynamicMatrix[pos.getX()][pos.getY()] = ' '; // tower char
}
void Map::add_pnj(Position pos) {
    dynamicMatrix[pos.getX()][pos.getY()] = ' '; // pnj char
}
void Map ::add_playerBase(Position pos) {
    dynamicMatrix[pos.getX()][pos.getY()] = ' '; // base char
}

void Map::update(GameState &gameState) {
    dynamicmatrix = matrix;
    for (auto &tower : gameState.getTowers()) {
        addTower(tower.getPosition());
    }

    for (auto &wave : gameState.getWaves()) {
        for (auto &pnj : wave.getPnjs()) {
            addNPC(pnj.getPosition());
        }
    }
    for (auto &playerstate: gameState.getPlayerStates()){
        if(playerstate.getHp() > 0){
            add_playerBase(//position de la base)
        }
    }
}

*/