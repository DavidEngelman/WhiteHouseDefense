

#include "MapGUI.hpp"


void MapGUI::generateTiles() {
    for (int x = 0; x < SIZE; x++){
        for (int y = 0; y < SIZE; y++) {
            if (x == 0 or x == SIZE-1 or y == 0 or y == SIZE-1) {
                tileMatrix[x][y] = matrix[y][x] == 0 ? CASTLE : matrix[y][x];
            } else {
                tileMatrix[x][y] = matrix[y][x] == 0 ? computeTile(Position(x, y)) : matrix[y][x];
            }
        }
    }
}

int MapGUI::computeTile(Position pos) {
    if (pos.getX() == SIZE/2 and pos.getY() == SIZE/2) return CROSS;

    bool up =       matrix[pos.getY()-1][pos.getX()] == 0;
    bool down =     matrix[pos.getY()+1][pos.getX()] == 0;
    bool left =     matrix[pos.getY()][pos.getX()-1] == 0;
    bool right =    matrix[pos.getY()][pos.getX()+1] == 0;

    if (up and down) return UP_DOWN;
    else if (left and right) return LEFT_RIGHT;
    else if (left and down) return LEFT_DOWN;
    else if (left and up) return LEFT_UP;
    else if (up and right) return UP_RIGHT;
    else return DOWN_RIGHT;
}

MapGUI::MapGUI(unsigned int seed) : Map(seed) { generateTiles(); }

void MapGUI::display(GameState &gameState, int quadrant) const {
    //Map::display(gameState, quadrant);
}

void MapGUI::setupGUI() {
    this->setFixedSize(TILES_SIZE*SIZE, TILES_SIZE*SIZE);
    this->show();
}

void MapGUI::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QImage image;

    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            switch (tileMatrix[x][y]) {
                case GRASS_INT:
                    image = QImage("../../qt_ui/game_pictures/tiles/grass.png");
                    break;
                case CROSS:
                    image = QImage("../../qt_ui/game_pictures/tiles/cross.png");
                    break;
                case UP_DOWN:
                    image = QImage("../../qt_ui/game_pictures/tiles/up_down.png");
                    break;
                case LEFT_RIGHT:
                    image = QImage("../../qt_ui/game_pictures/tiles/left_right.png");
                    break;
                case LEFT_DOWN:
                    image = QImage("../../qt_ui/game_pictures/tiles/left_down.png");
                    break;
                case LEFT_UP:
                    image = QImage("../../qt_ui/game_pictures/tiles/left_up.png");
                    break;
                case UP_RIGHT:
                    image = QImage("../../qt_ui/game_pictures/tiles/up_right.png");
                    break;
                case DOWN_RIGHT:
                    image = QImage("../../qt_ui/game_pictures/tiles/down_right.png");
                    break;
                case CASTLE:
                    image = QImage("../../qt_ui/game_pictures/tiles/castle.png");
                    break;
                default:
                    image = QImage("../../qt_ui/game_pictures/tiles/limit.png");
                    break;
            }
            painter.drawImage(x*TILES_SIZE, y*TILES_SIZE, image);
        }
    }
}
