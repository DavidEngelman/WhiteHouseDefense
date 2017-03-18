

#include "MapGUI.hpp"
#include "Game/GameGUI.hpp"

MapGUI::MapGUI(unsigned int seed, GameGUI *gameGUI, QHBoxLayout *layout = 0) : Map(seed), gameGUI(gameGUI) {
    display();
    layout->addWidget(this);
    if (seed == 0) this->setStyleSheet("background-image: url(../../maps/map1.png)");
    else if (seed == 1) this->setStyleSheet("background-image: url(../../maps/map2.png)");
    else if (seed == 2) this->setStyleSheet("background-image: url(../../maps/map3.png)");
}
MapGUI::MapGUI(unsigned int seed) : AbstractGUI(nullptr), Map(seed) { display(); }

void MapGUI::display(GameState &gameStateUpdate, int quadrantUpdate) {
    gameState = gameStateUpdate;
    quadrant = quadrantUpdate;
    update();
}

void MapGUI::display() {
    highlighted = Position(-1, -1); // Flag value
    this->setFixedSize(TILES_SIZE*SIZE, TILES_SIZE*SIZE);
    this->show();
}

void MapGUI::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QImage image;

    std::vector<AbstractTower *> &towers = gameState.getTowers();
    std::vector<Wave> &waves = gameState.getWaves();
    std::string &mode = gameState.getMode();

    std::string typeOfTower;
    bool has_npc;
    int cell;

    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            cell = matrix[y][x];
            if (cell == PATH_INT) {
                has_npc = false;
                for (auto &wave : waves) {
                    std::vector<PNJ> &pnjs = wave.getPnjs();
                    for (auto &pnj : pnjs) {
                        Position pos = pnj.getPosition();
                        if (x == pos.getX() && y == pos.getY()) {
                            has_npc = true;
                            break;
                        }
                    }
                    if (has_npc) break;
                }
//                image = QImage("../../qt_ui/game_pictures/tiles/path.png");
//                painter.drawImage(x*TILES_SIZE, y*TILES_SIZE, image);
                if (has_npc) {
                    image = QImage("../../qt_ui/game_pictures/tiles/mexican.png");
                    painter.drawImage(x*TILES_SIZE, y*TILES_SIZE, image);
                }
            } else if (cell == GRASS_INT or cell == SAND_INT or cell == SNOW_INT or cell == DIRT_INT or cell == STONE_INT) {
//                if (cell == GRASS_INT) {
//                    image = QImage("../../qt_ui/game_pictures/tiles/grass.png");
//                } else if (cell == SAND_INT) {
//                    image = QImage("../../qt_ui/game_pictures/tiles/sand.png");
//                } else if (cell == SNOW_INT) {
//                    image = QImage("../../qt_ui/game_pictures/tiles/snow.png");
//                } else if (cell == DIRT_INT) {
//                    image = QImage("../../qt_ui/game_pictures/tiles/dirt.png");
//                } else {
//                    image = QImage("../../qt_ui/game_pictures/tiles/stone.png");
//                }

                typeOfTower = "";
                for (auto &tower : towers) {
                    Position pos = tower->getPosition();
                    if (x == pos.getX() && y == pos.getY()) {
                        typeOfTower = tower->getType();
                        break;
                    }
                }
                if (typeOfTower != "") {
                    if (typeOfTower == GUN_TOWER_STR) {
                        image = QImage("../../qt_ui/game_pictures/tiles/guntower.png");
                    } else if (typeOfTower == SNIPER_TOWER_STR) {
                        image = QImage("../../qt_ui/game_pictures/tiles/snipertower.png");
                    } else if (typeOfTower == SHOCK_TOWER_STR) {
                        image = QImage("../../qt_ui/game_pictures/tiles/shocktower.png");
                    }
                    painter.drawImage(x * TILES_SIZE, y * TILES_SIZE, image);
                }
            } else if (cell == BASE_INT) {
                if (computeQuadrant(Position(x, y)) == quadrant) {
                    image = QImage("../../qt_ui/game_pictures/tiles/greenbase.png");
                } else {

                    if ((mode == TEAM_MODE) && (PARTNERS[computeQuadrant(Position(x, y))] == quadrant)) {
                        image = QImage("../../qt_ui/game_pictures/tiles/purplebase.png");
                    } else {
                        image = QImage("../../qt_ui/game_pictures/tiles/base.png");
                    }
                }
                painter.drawImage(x*TILES_SIZE, y*TILES_SIZE, image);
            }
//            else if (cell == GRASS_ROCK_INT) {
//                image = QImage("../../qt_ui/game_pictures/tiles/grassrock.png");
//            } else if (cell == TREE_INT) {
//                image = QImage("../../qt_ui/game_pictures/tiles/tree.png");
//            } else if (cell == PINE_INT) {
//                image = QImage("../../qt_ui/game_pictures/tiles/pine.png");
//            } else if (cell == PALMER_INT) {
//                image = QImage("../../qt_ui/game_pictures/tiles/palmer.png");
//            } else if (cell == WATER_INT) {
//                image = QImage("../../qt_ui/game_pictures/tiles/water.png");
//            } else if (cell == SAND_STONE_INT) {
//                image = QImage("../../qt_ui/game_pictures/tiles/sandstone.png");
//            } else if (cell == SAND_ROCK_INT) {
//                image = QImage("../../qt_ui/game_pictures/tiles/sandrock.png");
//            } else if (cell == WATER_ROCK_INT) {
//                image = QImage("../../qt_ui/game_pictures/tiles/waterrock.png");
//            } else if (cell == LAVA_INT) {
//                image = QImage("../../qt_ui/game_pictures/tiles/lava.png");
//            } else if (cell == PINE_SNOW_INT) {
//                image = QImage("../../qt_ui/game_pictures/tiles/pinesnow.png");
//            } else if (cell == DIRT_ROCK_INT) {
//                image = QImage("../../qt_ui/game_pictures/tiles/dirtrock.png");
//            }

            if (highlighted.getX() == x && highlighted.getY() == y) {
                QRect rect = QRect(x*TILES_SIZE, y*TILES_SIZE, TILES_SIZE-1, TILES_SIZE-1);
                painter.setPen(QColor(255, 0, 0));
                painter.drawRect(rect);
            }
        }
    }
}

void MapGUI::mousePressEvent(QMouseEvent* event) {
    Position pos = Position(event->x()/TILES_SIZE, event->y()/TILES_SIZE);
    if (highlighted == pos) {
        highlighted = Position(-1, -1); // Unselect the cell
        gameGUI->disableTowerShop();
    } else {
        highlighted = pos;
        if (isObstacle(pos) or isPath(pos) or isBase(pos)) gameGUI->disableTowerShop();
        else gameGUI->enableTowerShop();
    }
}
