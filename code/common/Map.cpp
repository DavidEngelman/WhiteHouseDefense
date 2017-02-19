#include "Map.hpp"
#include <fstream>
#include <iostream>
#include <ctime>

Map::Map() {
    generateRandomMatrix();
}

Map::Map(std::string filename) {
    std::ifstream mapFile;
    mapFile.open(filename, std::ios::in);

    if (mapFile.fail()) {
        std::cerr << "Failed to open the file" << std::endl;
        std::cerr << "Creating a random map instead" << std::endl;
        generateRandomMatrix();
        return;
    }

    std::string line;
    for (int x = 0; x < HEIGHT; x++) {
        getline(mapFile, line);
        for (int y = 0; y < WIDTH; y++) {
            switch (line[y]) {
                case 'o':
                    matrix[x][y] = x+y*WIDTH;
                    break;
                case '#':
                    matrix[x][y] = -1;
                    break;
                case ';':
                    matrix[x][y] = -2;
                    break;
                case '|':
                    matrix[x][y] = -3;
                    break;
                default:
                    matrix[x][y] = 0;
                    break;
            }
        }
    }

}

void Map::display() {
    std::cout << std::string(50, '\n');
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
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
    Pos begin;
    begin.y = HEIGHT/2-2;
    begin.x = WIDTH/2;
    srand((unsigned)time(0));
    generateQuarterMap(begin);
    display();
}

void Map::initMap() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (x == WIDTH/2 and HEIGHT/2-2 <= y and y <= HEIGHT/2+2) {
                matrix[y][x] = 0;
            } else if (y == HEIGHT/2 and WIDTH/2-2 <= x and x <= WIDTH/2+2) {
                matrix[y][x] = 0;
            } else if (x == y or x + y == HEIGHT-1) {
                matrix[y][x] = -2;
            } else {
                matrix[y][x] = -1;
            }
        }
    }
    matrix[HEIGHT/2][WIDTH/2] = 0;
}

bool Map::generateQuarterMap(Map::Pos end) {
    if (end.y == 0) {
        return true;
    }

    std::vector<Pos> possibleWays;
    Pos nextToEnd;

    nextToEnd.y = end.y-1;
    nextToEnd.x = end.x;
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

std::string Map::posToString(Map::Pos position) {
    return "(" + std::to_string(position.y) + ", " + std::to_string(position.x) + ")";
}

bool Map::isNextToPath(Map::Pos position) {
    int count = 0;
    if (matrix[position.y+1][position.x] == 0) count++;
    if (matrix[position.y-1][position.x] == 0) count++;
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
