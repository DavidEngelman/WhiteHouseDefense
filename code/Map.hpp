#ifndef MAP_HPP
#define MAP_HPP

#include <string>

class Map {
private:
    static const int height = 20;
    static const int width = 20;
    int matrix[width][height];

public:
    Map();
    Map(std::string filename);
    void display();
};

#endif
