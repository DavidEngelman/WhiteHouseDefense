

#include "AbstractManager.hpp"

void AbstractManager::setMusicFromPath(QString path) {
    master_app->setMusicFromPath(path);
}

void AbstractManager::centerWindow() {
    master_app->centerWindow();
}
