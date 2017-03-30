

#ifndef PROJET_MAPGUI_HPP
#define PROJET_MAPGUI_HPP
static const short GUN_TOWER = 0;
static const short SHOCK_TOWER = 1;
static const short SNIPER_TOWER = 2;
static const short MISSILE_TOWER = 3;
static const short MEXICAN = 0;
static const short MUSLIM = 1;
static const short COMMUNIST = 2;
static const short FROZEN_MEXICAN = 4;
static const short FROZEN_MUSLIM = 5;
static const short FROZEN_COMMUNIST = 3;




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
    std::vector<QImage> tower_images = {QImage("../../qt_ui/resources/tiles/guntower.png"),
                                        QImage("../../qt_ui/resources/tiles/shocktower.png"),
                                        QImage("../../qt_ui/resources/tiles/snipertower.png"),
                                        QImage("../../qt_ui/resources/tiles/missiletower.png")};

    std::vector<QImage> NPC_images = {QImage("../../qt_ui/resources/tiles/mexican.png"),
                                      QImage("../../qt_ui/resources/tiles/muslim.png"),
                                      QImage("../../qt_ui/resources/tiles/communist.png"),
                                      QImage("../../qt_ui/resources/tiles/frozenCommunist.png"),
                                      QImage("../../qt_ui/resources/tiles/frozenMexican.png"),
                                      QImage("../../qt_ui/resources/tiles/frozenMuslim.png")};


protected:

    void paintEvent(QPaintEvent *event) override;

public:

    MapGUI(unsigned int seed, GameGUI *gameGUI, QVBoxLayout *layout);

    void display();

    void display(GameState &gameState, int quadrant) override;

    void mousePressEvent(QMouseEvent *event) override;

    Position getHighlightedPosition() const override { return highlighted; }

    bool isEnemyBaseInHighlightedPosition(int quadrant) override;
};


#endif //PROJET_MAPGUI_HPP
