#include "GameEngine.hpp"

GameEngine::GameEngine(): numOfPNJsPerWave(10) {
    timer.start();
}

/*
 * Updates the game state by one tick.
 * Returns true if the wave (or game) is finished, false otherwise.
 */
bool GameEngine::update() {
    int numMilisecondsSinceStart = timer.elapsedTimeInMiliseconds();
    int numStepsToDo = (numMilisecondsSinceStart / STEP_DURATION) - numStepsDone;
    for (int i = 0; i < numStepsToDo; ++i) {
        updateWaves();
        updatePlayerStates();
    }
    return gameState.isFinished() || gameState.isRoundFinished();
}

void GameEngine::updateWaves() {
    std::vector<Wave> &waves = gameState.getWaves();
    dealDamage(waves);
    removeDeadPNJs(); //avant de faire faire avancer les pnj on enlève les morts
    movePNJsInWaves(waves);
}

void GameEngine::updatePlayerStates() {
    std::vector<PlayerState> &playerStates = gameState.getPlayerStates();
    dealDamageToBase(playerStates);
}

void GameEngine::dealDamageToBase(std::vector<PlayerState> &playerStates) {
    for (Wave &wave : gameState.getWaves()) {
        PlayerState &player_state = getPlayerStateForWave(wave);

        for (PNJ &pnj : wave.getPnjs()) {
            if (pnj.isInPlayerBase()) {
                player_state.decrease_hp(PNJ_DAMAGE);
                pnj.setHealthPoints(0);
                // TODO: Faudrait enlever ces PNJ de la vague...
                // C'est fait dans updateWaves au round suivant, mais c'est pas evident tout de suite
            }
        }
        //wave.removeDeadPNJs();
    }
}

void GameEngine::dealDamage(std::vector<Wave> &waves) {
    for (AbstractTower &tower: gameState.getTowers()) {
        Wave &wave = getWaveInSameQuadrant(tower, waves);
        bool killedPNJ = tower.shoot(wave);
        if (killedPNJ){
            PlayerState player_state = getPlayerStateForWave(wave);
            giveGold(player_state);
        }
    }
}

PlayerState &GameEngine::getPlayerStateForWave(Wave &wave) {
    int quadrant = wave.getQuadrant();
    return gameState.getPlayerStates()[quadrant];
}

void GameEngine::giveGold(PlayerState& playerState){
    playerState.earnMoney(PNJ_VALUE);
}

void GameEngine::movePNJsInWaves(std::vector<Wave> &waves) {
    for (Wave &wave: waves) {
        movePNJsInWave(wave);
    }
}

void GameEngine::movePNJsInWave(Wave &wave) {
    for (PNJ &pnj: wave.getPnjs()) {
        pnj.advance(gameState.getMap());
    }
}

Wave &GameEngine::getWaveInSameQuadrant(AbstractTower &tower, std::vector<Wave> &waves) {
    int quadrant = tower.getQuadrant();
    for (Wave &wave: waves) {
        if (quadrant == wave.getQuadrant()) {
            return wave;
        }
    }
}

void GameEngine::removeDeadPNJs() {
    for (Wave &wave : gameState.getWaves()) {
        wave.removeDeadPNJs();
    }
}

void GameEngine::createWaves() {
    gameState.clearWaves();
    increaseWaveDifficulty();
    for (const int direction: DIRECTIONS) {
        Wave wave(numOfPNJsPerWave, direction);
        // Ici je passe par valeur... si je passe par reference, je ne sais pas si ça va continuer
        // à exister à la sortie du bloc.
        // TODO: verifier
        gameState.addWave(wave);
    }
}

void GameEngine::increaseWaveDifficulty() {
    numOfPNJsPerWave += 5;
}

bool GameEngine::isGameFinished() {
    return gameState.isFinished();
}

std::string * GameEngine::serializeGameState() {
    return gameState.serialize();
}

GameState &GameEngine::getGameState(){
    return gameState;
}
