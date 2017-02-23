#include "GameState.hpp"

void GameState::decrease_player_hp(PlayerState& player, int amount){
    player.decrease_hp(amount);
}

void GameState::increase_player_hp(PlayerState& player, int amount){
    player.decrease_hp(amount);
}

std::string GameState::serialize() {
    std::string serialized_me;

    for (PlayerState& pstate: player_states){
        // C'est un peu bizarre comme fonction. Intuitivement, on dirait qu'il va
        // mettre le resultat dans serialized_me, au lieu de faire un append.
        // C'est ce que j'ai pensé quand j'ai vu ça
        serialized_me += pstate.serialize();
    }
    for (AbstractTower& tower: towers){
        serialized_me += tower.serialize();
    }
    for (Wave& wave: waves){
        serialized_me += wave.serialize();
    }

    return serialized_me;
}

void GameState::add_tower(Position position) {
    // TODO: il faut modifier cette fonction, car on ne sait pas de quel type de tour on parle
    // il faut soit prendre un parametre de plus (le type), soit modifier la signature pour
    // qu'elle prenne une AbstractTower
//        towers.push_back(Tower tower);
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
bool GameState::isFinished() {
    // TODO
}

void GameState::move_waves_forward(){
    for (Wave& wave: waves){

    }

}

bool GameState::can_go_forward(int wave_id, Position &current_pos) {
    Direction dir  = get_forward_direction(wave_id);

    Position forward_pos = Position(current_pos.getX() + dir.x, current_pos.getY() + dir.y);

    if (map.is_path(forward_pos)){
        return true;
    }
    return false;


}

bool GameState::can_go_left(int wave_id, Position &current_pos, Position& last_pos) {
    Direction dir  = get_left_direction(wave_id);

    Position letf_pos = Position(current_pos.getX() + dir.x, current_pos.getY() + dir.y);

    if (map.is_path(letf_pos) && letf_pos != last_pos){
        //TODO implement != for position
        return true;
    }
    return false;


}
bool GameState::can_go_right(int wave_id, Position& current_pos, Position& last_pos) {
    Direction dir  = get_right_direction(wave_id);

    Position right_pos = Position(current_pos.getX() + dir.x, current_pos.getY() + dir.y);

    if (map.is_path(right_pos) && right_pos != last_pos){
        //TODO implement != for position
        return true;
    }
    return false;


}

Direction GameState::get_forward_direction(int wave_id) {
    Direction direction;

    if (wave_id == 0){ // wave du haut

        direction.x = 0;
        direction.y = 1;
        return direction;

    }

    else if (wave_id == 1){ // wave de droite

        direction.x = 1;
        direction.y = 0;
        return direction;

    }

    else if (wave_id == 2){ // wave du bas

        direction.x = 0;
        direction.y = -1;
        return direction;

    }

    else if (wave_id == 3){ // wave de gauche

        direction.x = 1;
        direction.y = 0;
        return direction;

    }

}

Direction GameState::get_right_direction(int wave_id) {
    Direction direction;

    if (wave_id == 0){ // wave du haut

        direction.x = 1;
        direction.y = 0;
        return direction;

    }

    else if (wave_id == 1){ // wave de droite

        direction.x = 0;
        direction.y = -1;
        return direction;

    }

    else if (wave_id == 2){ // wave du bas

        direction.x = 1;
        direction.y = 0;
        return direction;

    }

    else if (wave_id == 3){ // wave de gauche

        direction.x = 0;
        direction.y = 1;
        return direction;

    }
}

Direction GameState::get_left_direction(int wave_id) {
    Direction direction;

    if (wave_id == 0){ // wave du haut

        direction.x = -1;
        direction.y = 0;
        return direction;

    }

    else if (wave_id == 1){ // wave de droite

        direction.x = 0;
        direction.y = 1;
        return direction;

    }

    else if (wave_id == 2){ // wave du bas

        direction.x = 1;
        direction.y = 0;
        return direction;

    }

    else if (wave_id == 3){ // wave de gauche

        direction.x = 0;
        direction.y = -1;
        return direction;

    }
}

