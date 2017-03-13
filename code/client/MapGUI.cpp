

#include "MapGUI.hpp"

MapGUI::MapGUI(unsigned int seed) : Map(seed) {}

void MapGUI::display(GameState &gameState, int quadrant) const {
    //Map::display(gameState, quadrant);
}

void MapGUI::display() {
    this->setFixedSize(TILES_SIZE*SIZE, TILES_SIZE*SIZE);
    this->show();
}

void MapGUI::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QImage image;

    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            switch (matrix[y][x]) {
                case GRASS_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/grass.png");
                    break;
                case PATH_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/cross.png");
                    break;
                case TREE_INT:
                    break;
                default:
                    image = QImage("../../qt_ui/game_pictures/tiles/limit.png");
                    break;
            }
            painter.drawImage(x*TILES_SIZE, y*TILES_SIZE, image);
        }
    }
}
