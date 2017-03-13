

#ifndef PROJET_MAPGUI_HPP
#define PROJET_MAPGUI_HPP

#define TILES_SIZE 16 // Size in pixel

#include <QtGui/QPainter>
#include "../common/Map.hpp"
#include "Abstract/AbstractGUI.hpp"

class MapGUI : public Map, public AbstractGUI {

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    MapGUI(unsigned int seed);
    void display();
    void display(GameState& gameState, int quadrant) const;
};


#endif //PROJET_MAPGUI_HPP
