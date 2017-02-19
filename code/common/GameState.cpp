#include "GameState.hpp"

void GameState::decrease_player_hp(PlayerState& player, int amount){
    player.decrease_hp(amount);
}

void GameState::increase_player_hp(PlayerState& player, int amount){
    player.decrease_hp(amount);
}

std::string GameState::serialize() {
    std::string serialized_me;

    for (PlayerState pstate: player_states){
        pstate.serialize(serialized_me);
    }
    for (Tower tower: towers){
        tower.serialize(serialized_me);
    }
    for (Wave wave: waves){
        wave.serialize(serialized_me);
    }
}

void GameState::add_tower(Position position) {
    // TODO
}
