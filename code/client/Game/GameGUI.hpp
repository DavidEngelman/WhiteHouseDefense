

#ifndef PROJET_GAMEGUI_HPP
#define PROJET_GAMEGUI_HPP


#include <QtWidgets/QLabel>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include "../Abstract/AbstractGUI.hpp"
#include "GameManager.hpp"
#include "GameUI.hpp"
#include "InGameChatWidget.hpp"
#include "../QCustomButton.h"

class MapGUI;

class GameGUI : public AbstractGUI, public GameUI {
    Q_OBJECT

private:
    QGroupBox *playerInfo;
    QLabel *usernameL;
    QLabel *playerStateL;

    QGroupBox *towerShop;
    QCustomButton *gunTowerB;
    QCustomButton *sniperTowerB;
    QCustomButton *shockTowerB;

    QGroupBox *deleteAndUpgradeBox;
    QCustomButton *deleteTowerB;
    QCustomButton *upgradeTowerB;

    QGroupBox *spellBox;


    InGameChatWidget * inGameChatWidget;

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

    void displayDeadMessage() ;

    void displayPlayersPlacingTowersMessage() override ;

    void disableTowerShop();
    void enableTowerShop();

    void displayDeleteAndUpgradeBox();

    void addChatMessage(const std::string &message, const std::string &sender) override;
};


#endif //PROJET_GAMEGUI_HPP
