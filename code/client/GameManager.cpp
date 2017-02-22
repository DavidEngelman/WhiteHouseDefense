
#include "GameManager.hpp"

GameManager::GameManager() {
    GameState playerGameState= GameState();
    GameUI gameUI = GameUI();
    placeTower();
}
void GameManager::placeTower(){
    std::string coord;
    gameUI.display();
    coord=gameUI.getCoordTower();

}
void GameManager::getReceivedChanges() {

}

void GameManager::displayWave() {
    gameUI.display();

}
