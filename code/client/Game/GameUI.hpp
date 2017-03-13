#ifndef GAMEUI_HPP
#define GAMEUI_HPP

#include "../../common/GameState.hpp"
#include "../../common/Map.hpp"
#include "../Drawing.hpp"
#include "../Abstract/AbstractUI.hpp"


class GameUI : public AbstractUI {
private:
    Map* map;

	bool checkCoord(int x, int y);

public:
    GameUI(unsigned seed);

	Position getPosBuyingTower();

	Map *getMap() const;

	Position getPosSellingTower();
	int getChoice();

	void display(GameState& gameState, int quadrant);
	void displayPosingPhase();
	void displayTowerShop();

	void displayGameOver(GameState& gamestate);

	void displayPlayerInfos(GameState &gameState, int quadrant);
	void displayInfoForSupporter(GameState& gameState);

	void display_dead_message();

    void displayPlayersPlacingTowersMessage();
};

#endif