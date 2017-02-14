#ifndef MAP_HPP
#define MAP_HPP

#define HEIGHT 20
#define WIDTH 20

#define GRASS "⬛"
#define PATH "⬜"
#define ERROR "❎"

#include <string>

class Map {
private:
    int matrix[HEIGHT][WIDTH];

public:
    Map();
    Map(std::string filename);
    void display();
    void generateRandomMatrix();
    bool isNextToPath(int x, int y);
};

#endif
