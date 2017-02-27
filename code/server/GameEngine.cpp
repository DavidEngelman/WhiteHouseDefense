#include "GameEngine.hpp"

const bool DEBUG = false;



GameEngine::GameEngine(unsigned int mapSeed) : map(mapSeed),
                                               numOfPNJsPerWave(INITIAL_NUMBER_OF_PNJS_PER_WAVE) {
    timerSinceGameStart.start();
}

/*
 * Updates the game state by one tick.
 * Returns true if the wave (or game) is finished, false otherwise.
 */

bool GameEngine::update() {
    int numMilisecondsSinceStart = timerSinceWaveStart.elapsedTimeInMiliseconds();
    int numStepsToDo = (numMilisecondsSinceStart / STEP_DURATION_IN_MS) - numStepsDone;
    for (int i = 0; i < numStepsToDo; ++i) {
        updateWaves();
        updatePlayerStates();
    }
    numStepsDone += numStepsToDo;
    return gameState.getIsGameOver() || gameState.isRoundFinished();
}

void GameEngine::updateWaves() {
    std::vector<Wave> &waves = gameState.getWaves();
    dealDamage(waves);
    removeDeadPNJsFromWaves();
    movePNJsInWaves(waves);
    addPNJS(waves);
    checkIfGameIsOver();
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
                if (!DEBUG) player_state.decrease_hp(PNJ_DAMAGE);
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
        if (killedPNJ && !DEBUG) {
            PlayerState player_state = getPlayerStateForWave(wave);
            addKillToStat(player_state);
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

void GameEngine::addKillToStat(PlayerState &playerState) {
    playerState.addOneKill();
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
    numStepsDone = 0;
    timerSinceWaveStart.reset();
    increaseWaveDifficulty();
    for (const int direction: DIRECTIONS) {
        // Je crée une vague uniquement si le joueur est vivant
        // Ça ne sert à rien de créer une vague vide
        if (DEBUG || gameState.isPlayerAlive(direction)) {
            Wave wave(numOfPNJsPerWave, direction);
            gameState.addWave(wave);
        }
    }
}

void GameEngine::increaseWaveDifficulty() {
    numOfPNJsPerWave += 1;
}

std::string *GameEngine::serializeGameState() {
    return gameState.serialize();
}

GameState &GameEngine::getGameState() {
    return gameState;
}

int min(int a, int b){
    return (a < b) ? a : b;
}

void GameEngine::addPNJS(std::vector<Wave> &waves) {
    for (Wave &wave: waves) {
        int currentNumOfPnjs = wave.getNumber_of_added_pnjs();
        int numOfPNJsInWave = wave.getNumber_of_pnjs();

        int numPnjsShouldHaveAdded = min(timerSinceWaveStart.elapsedTimeInMiliseconds() / 1000, numOfPNJsInWave);
        int numPNJsToAdd = numPnjsShouldHaveAdded - currentNumOfPnjs;

        if (numPNJsToAdd > 0) {
            for (int i = 0; i < numPNJsToAdd; ++i) {
                wave.addPNJ();
            }
        }
    }
}


void GameEngine::addTower(AbstractTower* tower, int quadrant) {
    if (!DEBUG) {
        if (gameState.getPlayerStates()[quadrant].getMoney() >=
            tower->getPrice()) {
            gameState.addTower(tower);
            gameState.getPlayerStates()[quadrant].spendMoney(tower->getPrice());
        }
    }
    else{
        gameState.addTower(tower);
    }
}

void GameEngine::deleteTower(Position position, int quadrant) {
    for (AbstractTower *tower : gameState.getTowers()){
        if (tower->getPosition() == position){
            gameState.getPlayerStates()[quadrant].earnMoney(tower->getPrice() * PERCENTAGE_RECOVERED_MONEY);
        }
    }
}


void GameEngine::showMap() {
    map.display(gameState);
}

void GameEngine::checkIfGameIsOver() {
    bool isOver = false;
    std::string &mode = gameState.getMode();
    if (mode == CLASSIC_MODE) {
        isOver = gameState.IsOnlyOnePlayerAlive();
    } else if (mode == TIMED_MODE) {
        // TODO: check que le timer commence depuis le debut de la premiere vague
        // au lieu de depuis la derniere vague
        isOver = timerSinceGameStart.elapsedTimeInSeconds() > TIMED_GAME_INTERVAL;
    } else if (mode == TEAM_MODE) {
        int numAlivePlayersInTeam1 = 0;
        int numAlivePlayersInTeam2 = 0;
        for (PlayerState& playerState: getGameState().getPlayerStates()) {
            if (playerState.getTeam() == 1) numAlivePlayersInTeam1++;
            else if (playerState.getTeam() == 2) numAlivePlayersInTeam2++;
        }

        isOver = ((numAlivePlayersInTeam1 == 0) || (numAlivePlayersInTeam2 == 0));
    }
    gameState.setIsGameOver(isOver);
}

bool GameEngine::isGameFinished() {
    return gameState.getIsGameOver();
}

void GameEngine::addPlayerState(int player_id) {
    addPlayerState(player_id, 0);
}

void GameEngine::addPlayerState(int player_id, int team) {
    PlayerState playerState(player_id, team);
    gameState.addPlayerState(playerState);
}


