#ifndef MAP_HPP
#define MAP_HPP

#define HEIGHT 21
#define WIDTH 21

#define GRASS "⬛"
#define PATH "⬜"
#define LIMIT "\033[34m❎\033[0m"
#define TOWER "\033[31m⬛\033[0m"
#define PNG "\033[33m⬛\033[0m"

#include <string>

class Map {
private:
    int matrix[HEIGHT][WIDTH];
    void generateRandomMatrix();
    void initMap();
    void generateQuarterMap();

public:
    Map();
    Map(std::string filename);
    void display();
};

#endif
