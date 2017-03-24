

#include "MapGUI.hpp"
#include "../Game/GameGUI.hpp"

MapGUI::MapGUI(unsigned int seed, GameGUI *gameGUI, QVBoxLayout *layout = 0) : Map(seed), gameGUI(gameGUI) {
    display();
    layout->addWidget(this);
    if (seed < NB_OF_MAPS) {
        std::string filename = "background-image: url(../../maps/map" + std::to_string(seed + 1) + ".png)";
        this->setStyleSheet(QString::fromStdString(filename));
    }
}

void MapGUI::display(GameState &gameStateUpdate, int quadrantUpdate) {
    gameState = gameStateUpdate;
    quadrant = quadrantUpdate;
    update();
}

void MapGUI::display() {
    highlighted = Position(-1, -1); // Flag value
    this->setFixedSize(TILES_SIZE * SIZE, TILES_SIZE * SIZE);
    this->show();
}

void MapGUI::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QImage image;

    std::vector<AbstractTower *> &towers = gameState.getTowers();
    std::vector<Wave> &waves = gameState.getWaves();
    std::string &mode = gameState.getMode();

    Position pos;
    std::string typeOfPNJ;

    for (auto &wave : waves) {
        std::vector<PNJ *> &pnjs = wave.getPnjs();
        for (auto &pnj : pnjs) {
            typeOfPNJ = pnj->getType();
            if (typeOfPNJ == MEXICAN_PNJ_STR) {
                image = QImage("../../qt_ui/game_pictures/tiles/mexican.png");
            } else if (typeOfPNJ == COMMUNIST_PNJ_STR) {
                image = QImage("../../qt_ui/game_pictures/tiles/communist.png");
            } else if (typeOfPNJ == MUSLIM_PNJ_STR) {
                image = QImage("../../qt_ui/game_pictures/tiles/muslim.png");
            }

            pos = pnj->getPosition();
            painter.drawImage(pos.getX(), pos.getY(), image);
        }
    }

    std::string typeOfTower;

    for (auto &tower : towers) {
        typeOfTower = tower->getType();

        if (typeOfTower == GUN_TOWER_STR) {
            image = QImage("../../qt_ui/game_pictures/tiles/guntower.png");
        } else if (typeOfTower == SNIPER_TOWER_STR) {
            image = QImage("../../qt_ui/game_pictures/tiles/snipertower.png");
        } else if (typeOfTower == SHOCK_TOWER_STR) {
            image = QImage("../../qt_ui/game_pictures/tiles/shocktower.png");
        } else {
            image = QImage("../../qt_ui/game_pictures/tiles/missiletower.png");
        }

        pos = tower->getPosition();
        int offset = image.height() - TILES_SIZE;
        painter.drawImage(pos.getX() * TILES_SIZE, pos.getY() * TILES_SIZE - offset, image);
    }

    QRect rect = QRect(highlighted.getX() * TILES_SIZE, highlighted.getY() * TILES_SIZE, TILES_SIZE - 1,
                       TILES_SIZE - 1);
    painter.setPen(QColor(255, 0, 0));
    painter.drawRect(rect);
}

void MapGUI::mousePressEvent(QMouseEvent *event) {
    Position pos = Position(event->x() / TILES_SIZE, event->y() / TILES_SIZE);
    if (highlighted == pos) {
        highlighted = Position(-1, -1); // Unselect the cell
        if (!gameGUI->isSupporter()) {
            gameGUI->disableTowerShop();
            gameGUI->disableDeleteAndUpgradeBox();
            gameGUI->disableAirStrike();
        }
    } else {
        highlighted = pos;
        if (!gameGUI->isSupporter()) {
            if (isObstacle(pos) or isPath(pos) or isBase(pos)) {
                gameGUI->disableTowerShop();
                gameGUI->disableDeleteAndUpgradeBox();
                if (isBase(pos)) {
                    std::cout << "here" << std::endl;
                    gameGUI->enableAirStrike();
                }
            } else {
                gameGUI->enableTowerShop();

            }
        }
    }
}

bool MapGUI::isEnnemyBaseInHighlightedPosition(int quadrant) {
    return isBase(highlighted) && computeQuadrant(highlighted) != quadrant;
}
