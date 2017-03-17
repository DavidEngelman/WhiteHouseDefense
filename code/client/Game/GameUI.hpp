

#ifndef PROJET_GAMEUI_H
#define PROJET_GAMEUI_H

#include "GameManager.hpp"
#include "../Abstract/AbstractUI.hpp"

class GameManager;

class GameUI : public virtual AbstractUI {

protected:

    GameManager *gameManager;

    Map* map;

public:
    GameUI(unsigned seed, GameManager *gameManager) : map(new Map(seed)), gameManager(gameManager) {};

    virtual Position getPosBuyingTower() = 0;

    virtual Map *getMap() const { return map ;}

    virtual Position getPosSellingTower() = 0;

    virtual void display(GameState& gameState, int quadrant) = 0;
    virtual void displayPosingPhase() = 0;
    virtual void displayTowerShop() = 0;

    virtual void displayGameOver(GameState& gamestate) = 0;

    virtual void displayPlayerInfos(GameState &gameState, int quadrant) = 0;
    virtual void displayInfoForSupporter(GameState& gameState) = 0;

    virtual void display_dead_message() = 0;

    virtual void displayPlayersPlacingTowersMessage() = 0;
    void displayPlayersPlacingTowersMessage();

    void destroy() {};
};

#endif //PROJET_GAMEUI_H
