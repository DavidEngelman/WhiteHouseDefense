

#include "GameGUI.hpp"

GameGUI::GameGUI(unsigned seed, GameManager *manager, QWidget* _parent) : AbstractGUI(_parent), GameUI(seed, manager) {}

Position GameGUI::getPosBuyingTower() {
    return Position();
}

void GameGUI::displayPlayersPlacingTowersMessage() {

}

Position GameGUI::getPosSellingTower() {
    return Position();
}

void GameGUI::display(GameState &gameState, int quadrant) {

}

void GameGUI::displayPosingPhase() {

}

void GameGUI::displayTowerShop() {

}

void GameGUI::displayGameOver(GameState &gamestate) {

}

void GameGUI::displayPlayerInfos(GameState &gameState, int quadrant) {

}

void GameGUI::displayInfoForSupporter(GameState &gameState) {

}

void GameGUI::display_dead_message() {

}
