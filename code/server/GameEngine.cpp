 #include "GameEngine.hpp"

GameEngine::GameEngine() {
    timer.start();
}

void GameEngine::update() {
    int numMilisecondsSinceStart = timer.elapsedTimeInMiliseconds();
    int numStepsToDo = (numMilisecondsSinceStart / STEP_DURATION) - numStepsDone;
    for (int i = 0; i < numStepsToDo; ++i) {
        updateWaves();
        updatePlayerStates();
    }
}

void GameEngine::updateWaves() {
    std::vector<Wave> &waves = gameState.getWaves();
    dealDamageToBase(waves);
    removeDeadPNJs(); //avant de faire faire avancer les pnj on enlève les morts
    movePNJsInWaves(waves);
}

void GameEngine::updatePlayerStates() {
    std::vector<PlayerState> &playerStates = gameState.getPlayerStates();
    dealDamageToBase(playerStates);
}

void GameEngine::dealDamageToBase(std::vector<PlayerState> &playerStates) {
    for (Wave& wave : gameState.getWaves()){
        for (PNJ& pnj : wave.getPnjs()){
            if (pnj.isInPlayerBase() && wave.getQuadrant() == NORTH){
                gameState.getPlayerStates()[0].decrease_hp(PNJ_DAMAGE);
                pnj.setHealthPoints(0);

            }
            else if (pnj.isInPlayerBase() && wave.getQuadrant() == EAST){
                gameState.getPlayerStates()[1].decrease_hp(PNJ_DAMAGE);
                pnj.setHealthPoints(0);

            }

            else if(pnj.isInPlayerBase() && wave.getQuadrant() == SOUTH){
                gameState.getPlayerStates()[2].decrease_hp(PNJ_DAMAGE);
                pnj.setHealthPoints(0);

            }
            else if(pnj.isInPlayerBase() && wave.getQuadrant() == WEST){
                gameState.getPlayerStates()[3].decrease_hp(PNJ_DAMAGE);
                pnj.setHealthPoints(0);
            }
        }
    }
}

void GameEngine::dealDamage(std::vector<Wave> &waves) {
    for (AbstractTower& tower: gameState.getTowers()){
        Wave& wave = getWaveInSameQuadrant(tower, waves);
        tower.shoot(wave);
    }
}

void GameEngine::movePNJsInWaves(std::vector<Wave> &waves) {
    for (Wave& wave: waves){
        movePNJsInWave(wave);
    }
}

void GameEngine::movePNJsInWave(Wave &wave) {
    for (PNJ& pnj: wave.getPnjs()){
        pnj.advance(gameState.getMap());
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

 void GameEngine::removeDeadPNJs(){
     for (Wave& wave : gameState.getWaves()){
         wave.removeDeadPNJs();
     }
 }
