#include "Map.hpp"
#include <fstream>
#include <iostream>
#include <ctime>

Map::Map() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {

            matrix[x][y] = 0;
        }
    }
}

Map::Map(std::string filename) {
    std::ifstream mapFile(filename);

    if (!mapFile) {
        std::cerr << "Failed to open the file" << std::endl;
        std::cerr << "Creating a random map instead" << std::endl;
        Map();
        return;
    }

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            matrix[x][y] = 0;
        }
    }

}

void Map::display() {
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            switch (matrix[x][y]) {
                case 0:
                    std::cout << "⬛";
                    break;
                case 1:
                    std::cout << "⬜";
                    break;
            }
        }
        std::cout << std::endl;
    }
}
