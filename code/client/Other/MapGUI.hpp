

#ifndef PROJET_MAPGUI_HPP
#define PROJET_MAPGUI_HPP

#include <QtGui/QPainter>
#include "../../common/Other/Map.hpp"
#include "../Abstract/AbstractGUI.hpp"
#include <QtGui/QMouseEvent>
#include <QtWidgets/QHBoxLayout>

class GameGUI;

class MapGUI : public QWidget, public Map {
private:
    GameState gameState;
    int quadrant;
    Position highlighted;

    GameGUI *gameGUI;

protected:
    void paintEvent(QPaintEvent *event) override;

public:
    MapGUI(unsigned int seed, GameGUI *gameGUI, QVBoxLayout *layout);
    void display();
    void display(GameState& gameState, int quadrant) override;

    void mousePressEvent(QMouseEvent *event) override ;
    Position getHighlightedPosition() const override { return highlighted; }
};


#endif //PROJET_MAPGUI_HPP
