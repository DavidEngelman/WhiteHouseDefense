

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
#define TILES_SIZE 16 // Size in pixel


#include <QtGui/QPainter>
#include "../common/Map.hpp"
#include "Abstract/AbstractGUI.hpp"

class MapGUI : public Map, public AbstractGUI {
private:
    int tileMatrix[SIZE][SIZE];

    void generateTiles();
    int computeTile(Position pos);

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    MapGUI(unsigned int seed);
    void setupGUI() {};
    void display();
    void display(GameState& gameState, int quadrant) const;
};


#endif //PROJET_MAPGUI_HPP
