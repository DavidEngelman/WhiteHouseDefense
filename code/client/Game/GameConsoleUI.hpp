#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include "../../common/GameState.hpp"
#include "../../common/Map.hpp"
#include "../Drawing.hpp"
#include "GameUI.hpp"
#include "../Abstract/AbstractConsoleUI.hpp"


class GameConsoleUI : public AbstractConsoleUI, public GameUI {


public:
	GameConsoleUI(unsigned seed, GameManager *gameManager);

	Position getPosBuyingTower() override ;

	Position getPosSellingTower() override ;
	int getChoice();

	void display(GameState& gameState, int quadrant) override ;
	void displayPlayerInfos(GameState &gameState, int quadrant) override ;
	void displayInfoForSupporter(GameState& gameState) override ;
	void displayTowerShop() override ;

	void displayGameOver(GameState& gamestate) override ;

	void displayPosingPhase();

	void displayDeadMessage() override ;

    void displayPlayersPlacingTowersMessage() override ;

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
};

#endif