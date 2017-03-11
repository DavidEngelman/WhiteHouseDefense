

#ifndef PROJET_MAPGUI_HPP
#define PROJET_MAPGUI_HPP

// Tiles
#define CROSS 0
#define UP_DOWN 1
#define LEFT_RIGHT 2
#define LEFT_DOWN 3
#define LEFT_UP 4
#define UP_RIGHT 5
#define DOWN_RIGHT 6
#define CASTLE 7


#include "../common/Map.hpp"
#include "Abstract/AbstractGUI.hpp"

class MapGUI : public Map, public AbstractGUI {
private:
    int tileMatrix[SIZE][SIZE];
    void generateTiles();
    int computeTile(Position pos);

public:
    MapGUI(unsigned int seed);
    void display(GameState& gameState, int quadrant) const;
};


#endif //PROJET_MAPGUI_HPP
