

#ifndef PROJET_GAMEGUI_HPP
#define PROJET_GAMEGUI_HPP


#include <QtWidgets/QLabel>
#include <QMessageBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include "../Abstract/AbstractGUI.hpp"
#include "GameManager.hpp"
#include "GameUI.hpp"
#include "InGameChatWidget.hpp"
#include "../Other/QCustomButton.hpp"
#include <QProgressBar>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include "../../common/Other/Tools.hpp"

QT_CHARTS_USE_NAMESPACE
class MapGUI;

class GameGUI : public AbstractGUI, public GameUI {
    Q_OBJECT

private:

    QHBoxLayout *mainLayout;

    // Left Panel
    QVBoxLayout* leftPanel;
    QLabel *usernameL;
    QGroupBox *playerStatsBox;
    QLabel *playerStateL;

    InGameChatWidget * inGameChatWidget;
    QGroupBox *chatBox;

    // Middle Panel
    QProgressBar *baseHealthBar;

    // Right Panel
    QVBoxLayout *actionLayout;
    QGroupBox *towerShop;
    QCustomButton *gunTowerB;
    QCustomButton *sniperTowerB;
    QCustomButton *shockTowerB;
    QCustomButton *missileTowerB;

    QGroupBox *deleteAndUpgradeBox;
    QPushButton *deleteTowerB;
    QPushButton *upgradeTowerB;

    QGroupBox *spellBox;
    QPushButton *nukeB;
    QPushButton *freezeB;
    QPushButton *airStrikeB;

    //base health of other players
    QGroupBox *otherPlayerHealthBarBox;
    std::vector<QProgressBar*> otherPlayerHealthBar;


    //end of game screen
    QWidget *endofGameWidget;
    QVBoxLayout *endOfGameLayout;

    QGroupBox *winnerLoserInfos;

    QHBoxLayout *statsLayout;
    QGroupBox *chartBox;
    QGridLayout *chartLayout;


    QChartView *chartView1;
    QChartView *chartView2;
    QChartView *chartView3;
    QChartView *chartView4;
    QChart *chart1;
    QChart *chart2;
    QChart *chart3;
    QChart *chart4;

    QBarSet *npcKilled;
    QBarSet *nbTowersPlaced;
    QBarSet *damageDealt;
    QBarSet *moneySpend;

    //supporter
    QGroupBox *supporterActionBox;
    QPushButton *adSpellB;

    QPushButton *backToMenu;


public slots:
    void handleBuyingTower(int typeOfTower);
    void handleSellingTower();
    void handleUpgradingTower();
    void handleNukeSpell();
    void handleAdSpell();
    void handleAirStrike();
    void goToMenu();

    void handleFreezeSpell();

public:
    GameGUI(bool isSupporter,unsigned seed, GameManager *manager);
    Position getPosBuyingTower() override ;


    Position getPosSellingTower() override ;
    
    void display(GameState& gameState, int quadrant) override ;
    void displayPlayerInfos(GameState &gameState, int quadrant) override ;
    void displayTowerShop() override ;

    void displayCurrentPlayerInfo(GameState &gameState, int quadrant) override;

    void displayGameOverAndStats(GameState &gamestate) override ;

    void displayInfoForSupporter(GameState& gameState, int quadrant) override ;

    void displayDeadMessage() ;

    void displayPlayersPlacingTowersMessage() override ;

    void disableTowerShop();
    void enableTowerShop();


    void displayDeleteAndUpgradeBox();

    void addChatMessage(const std::string &message, const std::string &sender) override;

    void disableNukeSpell() override ;
    void enableNukeSpell() override ;

    void disableDeleteAndUpgradeBox();

    void enableDeleteAndUpgradeBox();

    void displaySpellBox();

    void setUpHealthBar();

    void updateHealthBar(int value);

    void updateOtherPlayerHealthBar(std::vector<PlayerState> &playerState, int quadrant);

    void setUpOtherPlayerHealthBar();

    void switchToEndGameDisplay();

    void setUpEndOfGameLayout(GameState &gameState);

    void setUpWinnerLooserBox(GameState &gameState);

    void setUpStatsLayout(GameState &gameState);

    void setUpChartBox(GameState &gameState);

    void enableFreezeSpell() override ;

    void disableFreezeSpell() override ;

    void setUpTowerShop();

    void setUpDeleteAndUpgradBox();

    void setUpSpellsBox();

    void setUpStatsBox();

    void updateHealthBarOfSupportedPlayer(int value);

    void setUpSpellsBoxForSupporter();

    void enableSpells() override ;

    void disableSpells() override ;

    void disableAirStrike() override;

    void enableAirStrike();

    void displaySupporterActionBox();

    void adPopUp() override;

    void playSound(QString soundPath);
};


#endif //PROJET_GAMEGUI_HPP
