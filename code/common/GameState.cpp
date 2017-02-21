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
        // C'est un peu bizarre comme fonction. Intuitivement, on dirait qu'il va
        // mettre le resultat dans serialized_me, au lieu de faire un append.
        // C'est ce que j'ai pensé quand j'ai vu ça
        serialized_me += pstate.serialize();
    }
    for (AbstractTower tower: towers){
        serialized_me += tower.serialize();
    }
    for (Wave wave: waves){
        serialized_me += wave.serialize();
    }

    return serialized_me;
}

void GameState::add_tower(Position position) {
    void GameState::add_tower() {
        towers.push_back(Tower tower);
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

bool GameState::isWaveFinished() {
    // TODO
}

