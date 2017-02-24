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
    dealDamage(waves);
    removeDeadPNJs(); //avant de faire faire avancer les pnj on enlève les morts
    movePNJsInWaves(waves);
}

void GameEngine::updatePlayerStates() {
    std::vector<PlayerState> &playerStates = gameState.getPlayerStates();
    dealDamage(playerStates);
}

void GameEngine::dealDamage(std::vector<PlayerState> &playerStates) {
    for (Wave& wave : gameState.getWaves()){
        for (PNJ& pnj : wave.getPnjs()){
            if(pnj.getPosition().getX() == -1 && pnj.getDirection() == WEST){
                //TODO diminuer la vie du joueur a gauche
            }
            else if(pnj.getPosition().getX() == 31 && pnj.getDirection() == EAST){
                //TODO diminuer la vie du joueur a droite
            }
            else if(pnj.getPosition().getY() == -1 && pnj.getDirection() == NORTH){
                //TODO diminuer la vie du joueur en haut
            }
            else if(pnj.getPosition().getY() == 31 && pnj.getDirection() == SOUTH){
                //TODO diminuer la vie du joueur en bas
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
