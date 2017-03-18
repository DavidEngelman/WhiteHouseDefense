

#ifndef PROJET_GAMEGUI_HPP
#define PROJET_GAMEGUI_HPP


#include <QtWidgets/QLabel>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include "../Abstract/AbstractGUI.hpp"
#include "GameManager.hpp"
#include "GameUI.hpp"

class MapGUI;

class GameGUI : public AbstractGUI, public GameUI {
    Q_OBJECT

private:
    QGroupBox *playerInfo;
    QLabel *usernameL;
    QLabel *playerStateL;

    QGroupBox *towerShop;
    QPushButton *gunTowerB;
    QPushButton *sniperTowerB;
    QPushButton *shockTowerB;

public slots:
    void update_map();
    void handleBuyingTower(int typeOfTower);

public:
    GameGUI(unsigned seed, GameManager *manager);
    Position getPosBuyingTower() override ;


    Position getPosSellingTower() override ;
    
    void display(GameState& gameState, int quadrant) override ;
    void displayPlayerInfos(GameState &gameState, int quadrant) override ;
    void displayTowerShop() override ;

    void displayGameOver(GameState& gamestate) override ;

    void displayInfoForSupporter(GameState& gameState) override ;

    void display_dead_message() override ;

    void displayPlayersPlacingTowersMessage() override ;

    void disableTowerShop();
    void enableTowerShop();
};


#endif //PROJET_GAMEGUI_HPP
