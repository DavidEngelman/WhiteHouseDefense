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
                default:
                    matrix[x][y] = 0;
                    break;
            }
        }
    }

}

void Map::display() {
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
                default:
                    std::cout << TOWER;
                    break;
            }
        }
        std::cout << std::endl;
    }
}

bool Map::isNextToPath(int x, int y) {
    //TODO
    return false;
}

void Map::generateRandomMatrix() {
    srand((unsigned int) time(NULL));
    int end = rand() % WIDTH;

    for (int x = 1; x < HEIGHT; x++) {
        for (int y = 0; y < WIDTH; y++) {
            if (y == end) matrix[0][y] = 0;
            else matrix[0][y] = -1;

            if (isNextToPath(x, y)) {
                matrix[x][y] = 0;
            } else {
                matrix[x][y] = -1;
            }
        }
    }
}
