

#include "MapGUI.hpp"
#include "Game/GameGUI.hpp"

MapGUI::MapGUI(unsigned int seed, GameGUI *gameGUI, QVBoxLayout *layout = 0) : Map(seed), gameGUI(gameGUI) {
    display();
    layout->addWidget(this);
    if (seed == 0) this->setStyleSheet("background-image: url(../../maps/map1.png)");
    else if (seed == 1) this->setStyleSheet("background-image: url(../../maps/map2.png)");
    else if (seed == 2) this->setStyleSheet("background-image: url(../../maps/map3.png)");
}

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
    std::string typeOfPNJ;
    int cell;

    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            cell = matrix[y][x];
            if (cell == PATH_INT) {
                typeOfPNJ = "";
                for (auto &wave : waves) {
                    std::vector<PNJ*> &pnjs = wave.getPnjs();
                    for (auto &pnj : pnjs) {
                        Position pos = pnj->getPosition();
                        if (x == pos.getX() && y == pos.getY()) {
                            typeOfPNJ = pnj->getType();
                            break;
                        }
                    }
                    if (typeOfPNJ != "") break;
                }

                if (typeOfPNJ == MEXICAN_PNJ_STR) {
                    image = QImage("../../qt_ui/game_pictures/tiles/mexican.png");
                    painter.drawImage(x*TILES_SIZE, y*TILES_SIZE, image);
                } else if (typeOfPNJ == COMMUNIST_PNJ_STR) {
                    image = QImage("../../qt_ui/game_pictures/tiles/communist.png");
                    painter.drawImage(x*TILES_SIZE, y*TILES_SIZE, image);
                } else if (typeOfPNJ == MUSLIM_PNJ_STR) {
                    image = QImage("../../qt_ui/game_pictures/tiles/muslim.png");
                    painter.drawImage(x*TILES_SIZE, y*TILES_SIZE, image);
                }
            } else if (cell == GRASS_INT or cell == SAND_INT or
                    cell == SNOW_INT or cell == DIRT_INT or cell == STONE_INT) {

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
        gameGUI->disableDeleteAndUpgradeBox();
    } else {
        highlighted = pos;
        if (isObstacle(pos) or isPath(pos) or isBase(pos)) {
            gameGUI->disableTowerShop();
            gameGUI->disableDeleteAndUpgradeBox();
        }
        else gameGUI->enableTowerShop();
    }
}
