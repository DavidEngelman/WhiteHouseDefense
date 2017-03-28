#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include "../../common/Gamestate/GameState.hpp"
#include "../../common/Other/Map.hpp"
#include "../Other/Drawing.hpp"
#include "GameUI.hpp"
#include "../Abstract/AbstractConsoleUI.hpp"


class GameConsoleUI : public AbstractConsoleUI, public GameUI {
private:
    pthread_t thr;
	bool isInTowerPhase;
    bool isPrintedGameStateOutdated;

public:
    GameConsoleUI(bool isSupporter, unsigned seed, GameManager *gameManager);

    Position getPosBuyingTower() override;

    Position getPosSellingTower() override;

    int getChoice(int maxValue);

    void display(GameState &gameState, int quadrant) override;

    void displayPlayerInfos(GameState &gameState, int quadrant) override;

    void displayCurrentPlayerInfo(GameState &gameState, int quadrant) override;

    void displayInfoForSupporter(GameState &gameState, int quadrant) override;

    void displayTowerShop() override;

    void displayGameOverAndStats(GameState &gamestate) override;

    void displayPosingPhase();

    void displayDeadMessage() override;

    void displayPlayersPlacingTowersMessage() override;

    bool checkCoord(int x, int y);

    void *input_thread();

    static void *staticInputThread(void *self);

    int getTowerTypeChoice();

    Position getPositionOfTowerPlacement();

    void placeTowerAction();

    void sellTowerAction();

    Position getPosUpgradeTower();

    void upgradeTower();

    void addChatMessage(const std::string &message, const std::string &sender) override;

    void disableNukeSpell() override;

    void enableNukeSpell() override;

    void disableFreezeSpell() override;

    void enableFreezeSpell() override;

	void disableAirStrike() override;

    void disableSpells() override;

    void enableSpells() override;

	void adPopUp() override;

	void disableTeamHeal() override;

	void sendPredefinedMessage();

    void displayPredefinedMessages();

    void handleWaveStart() override;

    void handlePlaceTowerPhaseStart() override;

    void displayMap(GameState &gameState, int quadrant);
};

#endif