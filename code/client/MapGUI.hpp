

#ifndef PROJET_MAPGUI_HPP
#define PROJET_MAPGUI_HPP

#define TILES_SIZE 16 // Size in pixel

#include <QtGui/QPainter>
#include "../common/Map.hpp"
#include "Abstract/AbstractGUI.hpp"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QHBoxLayout>

class MapGUI : public Map, public QWidget {
private:
    GameState gameState;
    int quadrant;
    Position highlighted;

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    MapGUI(unsigned int seed, QWidget *parent, QHBoxLayout *layout);
    void display();
    void display(GameState& gameState, int quadrant) override;

    void mousePressEvent(QMouseEvent *event) override ;
};


#endif //PROJET_MAPGUI_HPP
