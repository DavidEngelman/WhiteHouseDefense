

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
                case PATH_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/path.png");
                    break;
                case GRASS_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/grass.png");
                    break;
                case BASE_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/base.png");
                    break;
                case GRASS_ROCK_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/grassrock.png");
                    break;
                case TREE_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/tree.png");
                    break;
                case PINE_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/pine.png");
                    break;
                case SAND_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/sand.png");
                    break;
                case PALMER_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/palmer.png");
                    break;
                case WATER_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/water.png");
                    break;
                case SAND_STONE_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/sandstone.png");
                    break;
                case SAND_ROCK_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/sandrock.png");
                    break;
                case WATER_ROCK_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/waterrock.png");
                    break;
                case LAVA_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/lava.png");
                    break;
                case SNOW_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/snow.png");
                    break;
                case PINE_SNOW_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/pinesnow.png");
                    break;
                case DIRT_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/dirt.png");
                    break;
                case DIRT_ROCK_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/dirtrock.png");
                    break;
                case STONE_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/stone.png");
                    break;
                default:
                    image = QImage("../../qt_ui/game_pictures/tiles/unknown.png");
                    break;
            }
            painter.drawImage(x*TILES_SIZE, y*TILES_SIZE, image);
        }
    }
}
