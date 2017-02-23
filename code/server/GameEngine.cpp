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

void GameEngine::move_waves_forward() {
    for(Wave& wave: gameState.getWaves()){
        move_wave_forward(wave);
    }
}

void GameEngine::move_wave_forward(Wave &wave) {
    // On commence par infliger des degats, puis on bouge les PNJ
    // Pas sur que l'ordre soit important

    for (PNJ& pnj: wave.getPnjs())

}
