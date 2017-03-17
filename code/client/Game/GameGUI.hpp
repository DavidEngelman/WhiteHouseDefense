

#ifndef PROJET_GAMEGUI_HPP
#define PROJET_GAMEGUI_HPP


#include "../Abstract/AbstractGUI.hpp"
#include "GameManager.hpp"
#include "GameUI.hpp"

class GameGUI : public AbstractGUI, public GameUI {

public:
    GameGUI(unsigned seed, GameManager *manager);
    Position getPosBuyingTower() override ;


    Position getPosSellingTower() override ;
    
    void display(GameState& gameState, int quadrant) override ;
    void displayPosingPhase() override ;
    void displayTowerShop() override ;

    void displayGameOver(GameState& gamestate) override ;

    void displayPlayerInfos(GameState &gameState, int quadrant) override ;
    void displayInfoForSupporter(GameState& gameState) override ;

    void display_dead_message() override ;

    void displayPlayersPlacingTowersMessage() override ;

};


#endif //PROJET_GAMEGUI_HPP
