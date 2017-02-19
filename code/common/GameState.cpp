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

    return serialized_me;
}

void GameState::add_tower(Position position) {
    // TODO
}

bool GameState::is_only_one_alive() {
    int nmbr_of_alive;
    for (PlayerState ps: player_states){
        if (ps.getHp() > 0){
            nmbr_of_alive++;
        }
    }
    return  (nmbr_of_alive == 1);
}

