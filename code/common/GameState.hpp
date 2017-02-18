#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <vector>
#include "PlayerState.hpp"
#include "Tower.hpp"
#include "PNJ.hpp"
#include "Map.hpp"

class GameState {

	std::vector<PlayerState> player_states;
	std::vector<Tower>       towers;
	std::vector<PNJ>         pnjs;

	Map map;



public:

	void decrease_player_hp(PlayerState& player, int amount);
    void increase_player_hp(PlayerState& player, int amount);

    void add_tower();

    void applyChanges(int changes);

	void updateGameState(int commands);
};
#endif