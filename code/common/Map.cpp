#include "Map.hpp"
#include <fstream>
#include <iostream>
#include <ctime>
#include <vector>

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
    //std::cout << std::string(50, '\n');
    std::cout << std::string(1, '\n');
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            switch (matrix[x][y]) {
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
    begin.x = HEIGHT/2-2;
    begin.y = WIDTH/2;
    generateQuarterMap(begin);
}

void Map::initMap() {
    for (int x = 0; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            if (y == WIDTH/2 and HEIGHT/2-2 <= x and x <= HEIGHT/2+2) {
                matrix[x][y] = 0;
            } else if (x == HEIGHT/2 and WIDTH/2-2 <= y and y <= WIDTH/2+2) {
                matrix[x][y] = 0;
            } else if (x == y or x + y == HEIGHT-1) {
                matrix[x][y] = -2;
            } else {
                matrix[x][y] = -1;
            }
        }
    }
    matrix[HEIGHT/2][WIDTH/2] = 0;
}

bool Map::generateQuarterMap(Map::Pos end) {
    //int quarter[HEIGHT/2][WIDTH];
    if (end.x == -1) {
        return true;
    }

    std::vector<Pos> possibleWays;
    Pos nextToEnd;

    nextToEnd.x = end.x-1;
    nextToEnd.y = end.y;
    if (!isNextToPath(nextToEnd)) possibleWays.push_back(nextToEnd);
    nextToEnd.x = end.x+1;
    if (!isNextToPath(nextToEnd)) possibleWays.push_back(nextToEnd);

    nextToEnd.x = end.x;
    nextToEnd.y = end.y-1;
    if (!isNextToPath(nextToEnd)) possibleWays.push_back(nextToEnd);
    nextToEnd.y = end.y+1;
    if (!isNextToPath(nextToEnd)) possibleWays.push_back(nextToEnd);

    srand((unsigned)time(0));
    unsigned int way = (unsigned int) (rand() % possibleWays.size());

    display();
    int save = matrix[possibleWays[way].x][possibleWays[way].y];

    if (save == -2) return true;

    matrix[possibleWays[way].x][possibleWays[way].y] = 0;
    if (generateQuarterMap(possibleWays[way])) return true;
    matrix[possibleWays[way].x][possibleWays[way].y] = save;
}

std::string Map::posToString(Map::Pos position) {
    return "(" + std::to_string(position.x) + ", " + std::to_string(position.y) + ")";
}

bool Map::isNextToPath(Map::Pos position) {
    int count = 0;
    if (matrix[position.x+1][position.y] == 0) count++;
    if (matrix[position.x-1][position.y] == 0) count++;
    if (matrix[position.x][position.y+1] == 0) count++;
    if (matrix[position.x][position.y-1] == 0) count++;
    return count >= 2;
}
