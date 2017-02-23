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

void GameEngine::updateWave(Wave &wave) {
    // On commence par infliger des degats, puis on bouge les PNJ
    // Pas sur que l'ordre soit important
    for (gameState.)

    for (PNJ& pnj: wave.getPnjs()){
        
    }

}

void GameEngine::dealDamage(std::vector<Wave> &waves) {
    for (AbstractTower& tower: gameState.getTowers()){
//        Wave wave = getWaveInSameQuandrant(tower, waves);
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


    }
}


