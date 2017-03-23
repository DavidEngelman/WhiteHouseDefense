

#ifndef PROJET_GAMEUI_H
#define PROJET_GAMEUI_H

#include "GameManager.hpp"
#include "../Abstract/AbstractUI.hpp"

class GameManager;

class GameUI : public virtual AbstractUI {

protected:

    GameManager *manager;
    Map *map;
    bool _isSupporter;

public:
    GameUI(bool isSupporter, unsigned seed, GameManager *manager) : _isSupporter(isSupporter),
                                                                    map(new Map(seed)),
                                                                    manager(manager) {};

    virtual Position getPosBuyingTower() = 0;

    virtual Map *getMap() const { return map; }

    virtual Position getPosSellingTower() = 0;

    virtual void display(GameState &gameState, int quadrant) = 0;

    virtual void displayPlayerInfos(GameState &gameState, int quadrant) = 0;

    virtual void displayCurrentPlayerInfo(GameState &gameState, int quadrant) = 0;

    virtual void displayInfoForSupporter(GameState &gameState, int quadrant) = 0;

    virtual void displayTowerShop() = 0;

    virtual void displayGameOverAndStats(GameState &gamestate) = 0;

    virtual void displayDeadMessage() = 0;

    virtual void displayPlayersPlacingTowersMessage() = 0;

    virtual void addChatMessage(const std::string &message, const std::string &sender) = 0;

    virtual void disableNukeSpell() = 0;

    virtual void enableNukeSpell() = 0;

    virtual void disableFreezeSpell() = 0;

    virtual void enableFreezeSpell() = 0;

    virtual void disableAirStrike() = 0;

    virtual void disableSpells() = 0;

    virtual void enableSpells() = 0;

    virtual void adPopUp() = 0;

    virtual bool isSupporter() const {
        return _isSupporter;
    };

    virtual void handlePlaceTowerPhaseStart() {};

    virtual void handleWaveStart() {};
};

#endif //PROJET_GAMEUI_H
