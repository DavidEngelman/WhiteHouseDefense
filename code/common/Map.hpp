#ifndef MAP_HPP
#define MAP_HPP

#define HEIGHT 21
#define WIDTH 21

#define GRASS "⬛"
#define PATH "⬜"
#define LIMIT "❎"
#define TOWER "\033[31m⬛\033[0m"

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
