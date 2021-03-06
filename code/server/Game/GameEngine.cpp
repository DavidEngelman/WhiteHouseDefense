#include "GameEngine.hpp"

GameEngine::GameEngine(unsigned int mapSeed, std::string mode) : map(mapSeed),
                                                                 numOfPNJsPerWave(INITIAL_NUMBER_OF_PNJS_PER_WAVE),
                                                                 gameState(mode) {
    timerSinceWaveStart.start();
    timerSinceGameStart.start();
}

/*
 * Updates the game state by one tick.
 * Returns true if the wave (or game) is finished, false otherwise.
 */

bool GameEngine::update() {
    int numMillisecondsSinceStart = timerSinceWaveStart.elapsedTimeInMiliseconds();
    int numStepsToDo = (numMillisecondsSinceStart / STEP_TRANSITION_DURATION) - currentTickNumber;
    for (int i = 0; i < numStepsToDo; ++i) {
        shootWaves();
        updateWaves();
        updatePlayerStates();
        removeDeadPNJsFromWaves();
        currentTickNumber += 1;
    }
    return gameState.getIsGameOver() || gameState.isRoundFinished();
}

void GameEngine::updateWaves() {
    std::vector<Wave> &waves = gameState.getWaves();
    movePNJsInWaves(waves);
    addPNJS(waves);
    checkIfGameIsOver();
}

void GameEngine::shootWaves() {
    if (currentTickNumber % NUM_TICKS_BETWEEN_SHOOTS != 0) return;
    dealDamage(gameState.getWaves());
}

void GameEngine::updatePlayerStates() {
    addMoney();
    dealDamageToBase();
}

void GameEngine::addMoney() {
    if (currentTickNumber % NUM_TICKS_BETWEEN_GOLD_EARNED != 0) return;
    for (PlayerState &player_state : gameState.getPlayerStates()) {
        player_state.earnMoney(GOLD_EARNED_BY_TICK);
        if (player_state.getIsSupported()) {
            player_state.earnMoney(GOLD_EARNED_BY_TICK);
        }
    }
}

void GameEngine::dealDamageToBase() {
    // Don't do anything during transition steps
    if (currentTickNumber % TRANSITIONS_TICKS_PER_STEP != 0) return;

    for (Wave &wave : gameState.getWaves()) {
        PlayerState &player_state = getPlayerStateForWave(wave);
        for (auto pnj : wave.getPnjs()) {
            if (pnj->isInPlayerBase()) {
                player_state.decrease_hp(pnj->getDamage());
                pnj->setHealthPoints(0);
                std::cout << "Killed a PNJ in ("
                          << pnj->getPosition().getX() << ","
                          << pnj->getPosition().getY() << ") and in transition position ("
                          << pnj->getTransitionPosition().getX() << ","
                          << pnj->getTransitionPosition().getY() << ")"
                          << std::endl;
                // On enleve pas les PNJ morts dans le vagues maintenant, parce que ça va
                // être fait dans updateWaves au round suivant
            }
        }
    }
}

void GameEngine::dealDamage(std::vector<Wave> &waves) {
    for (AbstractTower *tower: gameState.getTowers()) {
        Wave * wave = getWaveInSameQuadrant(*tower, waves);
        if (wave == nullptr) { continue; }

        const std::vector<PNJ *> &killedPNJ = tower->shoot(*wave, getPlayerStateForWave(*wave));
        for (auto &&pnj : killedPNJ) {
            PlayerState &player_state = getPlayerStateForWave(*wave);
            addKillToStat(player_state);
            giveGold(player_state, pnj);
        }
    }
}

PlayerState &GameEngine::getPlayerStateForWave(Wave &wave) {
    int quadrant = wave.getQuadrant();
    return gameState.getPlayerStates()[quadrant];
}

void GameEngine::giveGold(PlayerState &playerState, PNJ *pnj) {
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

Wave * GameEngine::getWaveInSameQuadrant(AbstractTower &tower, std::vector<Wave> &waves) {
    int quadrant = tower.getQuadrant();
    for (Wave &wave: waves) {
        if (quadrant == wave.getQuadrant()) {
            return &wave;
        }
    }
    return nullptr;
}

void GameEngine::removeDeadPNJsFromWaves() {
    for (Wave &wave : gameState.getWaves()) {
        wave.removeDeadPNJs();
    }
}

void GameEngine::createWaves() {
    gameState.clearWaves();
    currentTickNumber = 0;
    timerSinceWaveStart.reset();
    increaseWaveDifficulty();
    for (const int direction: DIRECTIONS) {
        // Je crée une vague uniquement si le joueur est vivant
        // Ça ne sert à rien de créer une vague vide
        if (gameState.isPlayerAlive(direction)) {
            Wave wave(numOfPNJsPerWave, direction);
            gameState.addWave(wave);
        } else {
            Wave wave(0, direction);
            gameState.addWave(wave);
        }
    }
}

void GameEngine::increaseWaveDifficulty() {
    numOfPNJsPerWave += NUMBER_OF_PNJS_ADDED_PER_WAVE;
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
                wave.addPNJ(rand() % NB_OF_TYPE_OF_PNJ);
            }
        }
    }
}


void GameEngine::addTower(AbstractTower *tower, int quadrant) {
    if (gameState.getPlayerStates()[quadrant].getMoney() >=
        tower->getPrice()) {
        gameState.addTower(tower, quadrant);
        getGameState().getPlayerStates()[quadrant].incrNbTowerPlaced();
        getGameState().getPlayerStates()[quadrant].incrMoneySpend(tower->getPrice());
    }
}

void GameEngine::deleteTower(Position &position, int &quadrant) {
    gameState.deleteTower(position, quadrant);
}

void GameEngine::upgradeTower(Position &position, int &quadrant) {
    gameState.upgradeTower(position, quadrant);

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
    for (PNJ *pnj : gameState.getWaves()[quadrant].getPnjs()) {
        damageDealt += pnj->getHealthPoints();
        pnj->setHealthPoints(0);
        getGameState().getPlayerStates()[quadrant].addOneKill();
    }
    getGameState().getPlayerStates()[quadrant].incrDamageDealt(damageDealt);
}

void GameEngine::freezeWave(int quadrant) {
    Wave &wave = gameState.getWaves()[quadrant];
    wave.freeze();
}

void GameEngine::launchAirStrike(int quadrant) {
    PlayerState &target = gameState.getPlayerStates()[quadrant];
    int target_current_hp = target.getHp();

    target.setHp(target_current_hp - min(target_current_hp, AIR_STRIKE_DAMAGE));

}

void GameEngine::teamHeal(int quadrant) {
    PlayerState &teammate = gameState.getPlayerStates()[PARTNERS[quadrant]];
    int teammate_cuurent_hp = teammate.getHp();

    if (teammate_cuurent_hp > 0) {
        teammate.setHp(teammate_cuurent_hp + min(PLAYER_STARTING_HP - teammate_cuurent_hp, HEAL_AMOUNT));
    }

}




