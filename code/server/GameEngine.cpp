#include "GameEngine.hpp"

GameEngine::GameEngine(unsigned int mapSeed) : map(mapSeed),
                                               numOfPNJsPerWave(INITIAL_NUMBER_OF_PNJS_PER_WAVE) {
    timer.start();
}

/*
 * Updates the game state by one tick.
 * Returns true if the wave (or game) is finished, false otherwise.
 */
bool GameEngine::update() {
    int numMilisecondsSinceStart = timer.elapsedTimeInMiliseconds();
    int numStepsToDo = (numMilisecondsSinceStart / STEP_DURATION_IN_MS) - numStepsDone;
    for (int i = 0; i < numStepsToDo; ++i) {
        updateWaves();
        updatePlayerStates();
    }
    return gameState.isFinished() || gameState.isRoundFinished();
}

void GameEngine::updateWaves() {
    std::vector<Wave> &waves = gameState.getWaves();
    addPNJS(waves);
    dealDamage(waves);
    removeDeadPNJsFromWaves();
    movePNJsInWaves(waves);
}

void GameEngine::updatePlayerStates() {
    std::vector<PlayerState> &playerStates = gameState.getPlayerStates();
    addMoney();
    dealDamageToBase();
}

void GameEngine::addMoney() {
    for (PlayerState &player_state : gameState.getPlayerStates()) {
        player_state.earnMoney(GOLD_EARNED_BY_SECOND);
    }
}

void GameEngine::dealDamageToBase() {
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
    for (AbstractTower * tower: gameState.getTowers()) {
        Wave &wave = getWaveInSameQuadrant(*tower, waves);
        bool killedPNJ = tower->shoot(wave);
        if (killedPNJ) {
            PlayerState player_state = getPlayerStateForWave(wave);
            giveGold(player_state);
        }
    }
}

PlayerState &GameEngine::getPlayerStateForWave(Wave &wave) {
    int quadrant = wave.getQuadrant();
    return gameState.getPlayerStates()[quadrant];
}

void GameEngine::giveGold(PlayerState &playerState) {
    playerState.earnMoney(PNJ_VALUE);
}

void GameEngine::movePNJsInWaves(std::vector<Wave> &waves) {
    for (Wave &wave: waves) {
        movePNJsInWave(wave);
    }
}

void GameEngine::movePNJsInWave(Wave &wave) {
    for (PNJ &pnj: wave.getPnjs()) {
        pnj.advance(map);
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

void GameEngine::removeDeadPNJsFromWaves() {
    for (Wave &wave : gameState.getWaves()) {
        wave.removeDeadPNJs();
    }
}

void GameEngine::createWaves() {
    gameState.clearWaves();
    increaseWaveDifficulty();
    for (const int direction: DIRECTIONS) {
        // Je crée une vague uniquement si le joueur est vivant
        // Ça ne sert à rien de créer une vague vide
        if (gameState.isPlayerAlive(direction)) {
            Wave wave(numOfPNJsPerWave, direction);
            gameState.addWave(wave);
        }
    }
}

void GameEngine::increaseWaveDifficulty() {
    numOfPNJsPerWave += 5;
}

bool GameEngine::isGameFinished() {
    return gameState.isFinished();
}

std::string *GameEngine::serializeGameState() {
    return gameState.serialize();
}

GameState &GameEngine::getGameState() {
    return gameState;
}

void GameEngine::addPNJS(std::vector<Wave> &waves) {
    for (Wave &wave: waves) {
        int currentNumOfPnjs = wave.getNumber_of_pnjs();
        int numPnjsShouldHaveAdded = timer.elapsedTimeInMiliseconds() / 1000;
        int numPNJsToAdd = numPnjsShouldHaveAdded - currentNumOfPnjs;


        if (currentNumOfPnjs < wave.getNumber_of_pnjs() && numPNJsToAdd > 0) {
            for (int i = 0; i < numPNJsToAdd; ++i) {
                wave.addPNJ();
            }
        }
    }
}


void GameEngine::addTower(AbstractTower* tower, int quadrant) {
    // TODO: check qu'il a assez d'argent
    gameState.addTower(tower);
    gameState.getPlayerStates()[quadrant].spendMoney(tower->getPrice());
}
