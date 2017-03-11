

#include "MapGUI.hpp"


void MapGUI::generateTiles() {
    for (int x = 0; x < SIZE; x++){
        for (int y = 0; y < SIZE; y++) {
            if (x == 0 or x == SIZE-1 or y == 0 or y == SIZE-1) {
                tileMatrix[x][y] = matrix[y][x] == 0 ? CASTLE : matrix[y][x];
            } else {
                tileMatrix[x][y] = matrix[y][x] == 0 ? computeTile(Position(x, y)) : matrix[y][x];
            }
        }
    }
}

int MapGUI::computeTile(Position pos) {
    if (pos.getX() == SIZE/2 and pos.getY() == SIZE/2) return CROSS;

    bool up =       matrix[pos.getY()-1][pos.getX()] == 0;
    bool down =     matrix[pos.getY()+1][pos.getX()] == 0;
    bool left =     matrix[pos.getY()][pos.getX()-1] == 0;
    bool right =    matrix[pos.getY()][pos.getX()+1] == 0;

    if (up and down) return UP_DOWN;
    else if (left and right) return LEFT_RIGHT;
    else if (left and down) return LEFT_DOWN;
    else if (left and up) return LEFT_UP;
    else if (up and right) return UP_RIGHT;
    else return DOWN_RIGHT;
}

MapGUI::MapGUI(unsigned int seed) : Map(seed) { generateTiles(); }

void MapGUI::display(GameState &gameState, int quadrant) const {

}
