#include "GameState.hpp"

void GameState::decrease_player_hp(PlayerState& player, int amount){
    player.decrease_hp(amount);
}

void GameState::increase_player_hp(PlayerState& player, int amount){
    player.decrease_hp(amount);
}

std::string GameState::serialize() {}