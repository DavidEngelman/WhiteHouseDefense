#include "GameEngine.hpp"
#include "../common/Constants.hpp"

const bool DEBUG = false;


GameEngine::GameEngine(unsigned int mapSeed, std::string mode) : map(mapSeed),
                                                                 numOfPNJsPerWave(INITIAL_NUMBER_OF_PNJS_PER_WAVE),
                                                                 gameState(mode) {
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
        player_state.earnMoney(GOLD_EARNED_BY_TICK);
        if (player_state.getIsSupported()) {
            player_state.earnMoney(GOLD_EARNED_BY_TICK);
        }
    }
}

void GameEngine::dealDamageToBase() {
    for (Wave &wave : gameState.getWaves()) {
        PlayerState &player_state = getPlayerStateForWave(wave);
        for (auto pnj : wave.getPnjs()) {
            if (pnj->isInPlayerBase()) {
                if (!DEBUG) player_state.decrease_hp(pnj->getDamage());
                pnj->setHealthPoints(0);
                // On enleve pas les PNJ morts dans le vagues maintenant, parce que ça va
                // être fait dans updateWaves au round suivant
            }
        }
    }
}

void GameEngine::dealDamage(std::vector<Wave> &waves) {
    for (AbstractTower *tower: gameState.getTowers()) {
        Wave &wave = getWaveInSameQuadrant(*tower, waves);
        const std::vector<PNJ *>& killedPNJ = tower->shoot(wave, getPlayerStateForWave(wave));
        for (auto &&pnj : killedPNJ) {
            if (DEBUG) break;
            PlayerState &player_state = getPlayerStateForWave(wave);
            addKillToStat(player_state);
            giveGold(player_state, pnj);
        }
    }
}

PlayerState &GameEngine::getPlayerStateForWave(Wave &wave) {
    int quadrant = wave.getQuadrant();
    return gameState.getPlayerStates()[quadrant];
}

void GameEngine::giveGold(PlayerState &playerState, PNJ* pnj) {
    playerState.earnMoney(pnj->getValue());
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
    for (auto pnj: wave.getPnjs()) {
        pnj->advance(map);
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

int min(int a, int b) {
    return (a < b) ? a : b;
}

void GameEngine::addPNJS(std::vector<Wave> &waves) {
    for (Wave &wave: waves) {
        int currentNumOfPnjs = wave.getNumber_of_added_pnjs();
        int numOfPNJsInWave = wave.getNumber_of_pnjs();

        int numPnjsShouldHaveAdded = min(timerSinceWaveStart.elapsedTimeInMiliseconds() /
                                         INTERVAL_BETWEEN_PNJS_IN_WAVE_IN_MS, numOfPNJsInWave);
        int numPNJsToAdd = numPnjsShouldHaveAdded - currentNumOfPnjs;

        if (numPNJsToAdd > 0) {
            srand((unsigned) time(0));
            for (int i = 0; i < numPNJsToAdd; ++i) {
                wave.addPNJ(rand()%NB_OF_TYPE_OF_PNJ);
            }
        }
    }
}


void GameEngine::addTower(AbstractTower *tower, int quadrant) {
    if (!DEBUG) {
        if (gameState.getPlayerStates()[quadrant].getMoney() >=
            tower->getPrice()) {
            gameState.addTower(tower, quadrant);
            getGameState().getPlayerStates()[quadrant].incrNbTowerPlaced();
            getGameState().getPlayerStates()[quadrant].incrMoneySpend(tower->getPrice());
        }
    } else {
        gameState.addTower(tower, quadrant);
    }
}

void GameEngine::deleteTower(Position &position, int &quadrant) {
    gameState.deleteTower(position, quadrant);
}

void GameEngine::upgradeTower(Position &position, int &quadrant) {
    for (AbstractTower *tower : getGameState().getTowers()) {
        if (tower->getPosition() == position) {
            float cost = (float) (tower->getPrice()) * (PERCENTAGE_RECOVERED_MONEY * (float) (tower->getLevel()));
            if (gameState.getPlayerStates()[quadrant].getMoney() - cost >= 0) {
                gameState.upgradeTower(position, quadrant);
                getGameState().getPlayerStates()[quadrant].incrMoneySpend(cost);
            }
        }
    }
}


void GameEngine::showMap() {
//    map.setUp(gameState);
}

void GameEngine::checkIfGameIsOver() {
    bool isOver = false;
    std::string &mode = gameState.getMode();
    if (mode == CLASSIC_MODE) {
        isOver = (gameState.numPlayersAlive() <= 1);
    } else if (mode == TIMED_MODE) {
        isOver = timerSinceGameStart.elapsedTimeInSeconds() > TIMED_GAME_DURATION;
    } else if (mode == TEAM_MODE) {
        int numAlivePlayersInTeam1 = 0;
        int numAlivePlayersInTeam2 = 0;
        for (PlayerState &playerState: getGameState().getPlayerStates()) {
            if (playerState.getTeam() == 1 && playerState.isAlive()) numAlivePlayersInTeam1++;
            else if (playerState.getTeam() == 2 && playerState.isAlive()) numAlivePlayersInTeam2++;
        }

        isOver = ((numAlivePlayersInTeam1 == 0) || (numAlivePlayersInTeam2 == 0));
    }

    gameState.setIsGameOver(isOver);
    if (isOver) declareWinner();
}


void GameEngine::declareWinner() {
    if (gameState.getMode() == CLASSIC_MODE) {
        declareWinnerInClassicMode();
    } else if (gameState.getMode() == TEAM_MODE) {
        declareWinnerTeam();
    } else if (gameState.getMode() == TIMED_MODE) {
        declareWinnerInTimedMode();
    }
}

void GameEngine::declareWinnerInTimedMode() {
    int maxScore = -1;
    for (auto &player : gameState.getPlayerStates()) {
        if (player.getPnjKilled() > maxScore) {
            maxScore = player.getPnjKilled();
        }
    }
    for (auto &player : gameState.getPlayerStates()) {
        if (player.getPnjKilled() == maxScore) {
            player.setIsWinner(true);
        }
    }
}

void GameEngine::declareWinnerInClassicMode() {
    for (auto &player : gameState.getPlayerStates()) {
        if (player.getHp() > 0) {
            player.setIsWinner(true);
        }
    }
}

void GameEngine::declareWinnerTeam() {
    int numPlayersAliveInTeam1 = 0;
    int numPlayersAliveInTeam2 = 0;
    for (auto &player : gameState.getPlayerStates()) {
        if (player.isAlive() && player.getTeam() == 1) {
            numPlayersAliveInTeam1 += 1;
        } else if (player.isAlive() && player.getTeam() == 2) {
            numPlayersAliveInTeam2 += 2;
        }
    }

    // If both team lose at the same time, no one wins
    if (numPlayersAliveInTeam1 == 0 && numPlayersAliveInTeam2 == 0) return;

    int winnerTeam = (numPlayersAliveInTeam1 > 0) ? 1 : 2;
    for (auto &player : gameState.getPlayerStates()) {
        if (player.getTeam() == winnerTeam) {
            player.setIsWinner(true);
        }
    }
}


bool GameEngine::isGameFinished() {
    return gameState.getIsGameOver();
}

void GameEngine::addPlayerState(int player_id, std::string username) {
    addPlayerState(player_id, username, 0);
}

void GameEngine::addPlayerState(int player_id, std::string username, int team) {
    PlayerState playerState(player_id, username, team);
    gameState.addPlayerState(playerState);
}

Timer &GameEngine::getTimerSinceGameStart() {
    return timerSinceGameStart;
}

void GameEngine::killAllNPC(int quadrant) {
    int damageDealt = 0;
    for(PNJ& pnj : gameState.getWaves()[quadrant].getPnjs()) {
        damageDealt += pnj.getHealthPoints();
        pnj.setHealthPoints(0);
        getGameState().getPlayerStates()[quadrant].addOneKill();
    }
    getGameState().getPlayerStates()[quadrant].incrDamageDealt(damageDealt);
}




