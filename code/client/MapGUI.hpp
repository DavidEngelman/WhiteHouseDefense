

#ifndef PROJET_MAPGUI_HPP
#define PROJET_MAPGUI_HPP

#define TILES_SIZE 16 // Size in pixel

#include <QtGui/QPainter>
#include "../common/Map.hpp"
#include "Abstract/AbstractGUI.hpp"

class MapGUI : public Map, public QWidget {
private:
    GameState gameState;
    int quadrant;

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    MapGUI(unsigned int seed, QWidget *parent);
    void display();
    void display(GameState& gameState, int quadrant) override;
};


#endif //PROJET_MAPGUI_HPP
