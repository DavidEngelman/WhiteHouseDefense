
#include "GameManager.hpp"
#include "../common/Networking.h"


GameManager::GameManager() {
    GameState gameState= GameState();
    GameUI gameUI = GameUI();
    placeTower();
}
void GameManager::placeTower(){
    std::string coord;
    gameUI.display();
    coord=gameUI.getCoordTower();
    //send_message(server_socket, coord.c_str());

}
void GameManager::getReceivedChanges() {

}

void GameManager::displayWave() {
    gameUI.display();

}
