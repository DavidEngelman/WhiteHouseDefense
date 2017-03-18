

#ifndef PROJET_GAMEUI_H
#define PROJET_GAMEUI_H

#include "GameManager.hpp"
#include "../Abstract/AbstractUI.hpp"

class GameManager;

class GameUI : public virtual AbstractUI {

protected:

    GameManager *manager;

    Map* map;

public:
    GameUI(unsigned seed, GameManager *manager) : map(new Map(seed)), manager(manager) {};

    virtual Position getPosBuyingTower() = 0;

    virtual Map *getMap() const { return map ;}

    virtual Position getPosSellingTower() = 0;

    virtual void display(GameState& gameState, int quadrant) = 0;
    virtual void displayPlayerInfos(GameState &gameState, int quadrant) = 0;
    virtual void displayInfoForSupporter(GameState& gameState) = 0;
    virtual void displayTowerShop() = 0;

    virtual void displayGameOver(GameState& gamestate) = 0;

    virtual void displayDeadMessage() = 0;

    virtual void displayPlayersPlacingTowersMessage() = 0;

    void addChatMessage(const std::string &message, const std::string &sender) {
        // TODO: implementer dans les sous classes
    }
};

#endif //PROJET_GAMEUI_H
