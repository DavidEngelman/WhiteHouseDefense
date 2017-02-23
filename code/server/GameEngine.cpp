//
//

#include "GameEngine.hpp"

GameEngine::GameEngine() {
    my_timer.start();
}

void GameEngine::update() {/*TODO*/}

void GameEngine::move_pnj_forward(PNJ &pnj) {
    Position current_pos = pnj.getPosition();


}

void GameEngine::updateWaves() {
    std::vector<Wave> &waves = gameState.getWaves();
    dealDamage(waves);
    movePNJsInWaves(waves);
}

void GameEngine::dealDamage(std::vector<Wave> &waves) {
    for (AbstractTower& tower: gameState.getTowers()){
        Wave& wave = getWaveInSameQuadrant(tower, waves);
        tower.attack(wave);
    }
}

void GameEngine::movePNJsInWaves(std::vector<Wave> &waves) {
    for (Wave& wave: waves){
        movePNJsInWave(wave);
    }
}

void GameEngine::movePNJsInWave(Wave &wave) {
    for (PNJ& pnj: wave.getPnjs()){
        pnj.advance(wave, gameState.getMap());
    }
}

Wave& GameEngine::getWaveInSameQuadrant(AbstractTower &tower, std::vector<Wave> &waves) {
    int quadrant = tower.getQuadrant();
    for (Wave& wave: waves) {
        if (quadrant == wave.getQuadrant()) {
            return wave;
        }
    }
}


bool GameEngine::can_go_forward(int wave_id, Position &current_pos) {
    Direction dir = get_forward_direction(wave_id);

    Position forward_pos = Position(current_pos.getX() + dir.x, current_pos.getY() + dir.y);

    if (map.is_path(forward_pos)) {
        return true;
    }
    return false;


}

bool GameEngine::can_go_left(int wave_id, Position &current_pos, Position &last_pos) {
    Direction dir = get_left_direction(wave_id);

    Position letf_pos = Position(current_pos.getX() + dir.x, current_pos.getY() + dir.y);

    if (map.is_path(letf_pos) && letf_pos != last_pos) {
        //TODO implement != for position
        return true;
    }
    return false;


}

bool GameEngine::can_go_right(int wave_id, Position &current_pos, Position &last_pos) {
    Direction dir = get_right_direction(wave_id);

    Position right_pos = Position(current_pos.getX() + dir.x, current_pos.getY() + dir.y);

    if (map.is_path(right_pos) && right_pos != last_pos) {
        //TODO implement != for position
        return true;
    }
    return false;


}

Direction GameEngine::get_forward_direction(int wave_id) {
    Direction direction;

    if (wave_id == 0) { // wave du haut

        direction.x = 0;
        direction.y = 1;
        return direction;

    } else if (wave_id == 1) { // wave de droite

        direction.x = 1;
        direction.y = 0;
        return direction;

    } else if (wave_id == 2) { // wave du bas

        direction.x = 0;
        direction.y = -1;
        return direction;

    } else if (wave_id == 3) { // wave de gauche

        direction.x = 1;
        direction.y = 0;
        return direction;

    }

}

Direction GameEngine::get_right_direction(int wave_id) {
    Direction direction;

    if (wave_id == 0) { // wave du haut

        direction.x = 1;
        direction.y = 0;
        return direction;

    } else if (wave_id == 1) { // wave de droite

        direction.x = 0;
        direction.y = -1;
        return direction;

    } else if (wave_id == 2) { // wave du bas

        direction.x = 1;
        direction.y = 0;
        return direction;

    } else if (wave_id == 3) { // wave de gauche

        direction.x = 0;
        direction.y = 1;
        return direction;

    }
}

Direction GameEngine::get_left_direction(int wave_id) {
    Direction direction;

    if (wave_id == 0) { // wave du haut

        direction.x = -1;
        direction.y = 0;
        return direction;

    } else if (wave_id == 1) { // wave de droite

        direction.x = 0;
        direction.y = 1;
        return direction;

    } else if (wave_id == 2) { // wave du bas

        direction.x = 1;
        direction.y = 0;
        return direction;

    } else if (wave_id == 3) { // wave de gauche

        direction.x = 0;
        direction.y = -1;
        return direction;

    }
}