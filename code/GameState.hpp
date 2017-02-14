#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

class GameState {


public:
	void applyChanges(int changes);

	void updateGameState(int commands);
};
#endif