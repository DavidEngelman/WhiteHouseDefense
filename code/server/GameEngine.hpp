#ifndef PROJET_GAMEENGINE_HPP
#define PROJET_GAMEENGINE_HPP

#include "../common/GameState.hpp"
#include "Timer.h"
#include "../common/Direction.h"
#include <iostream>
#include "../common/AttackTower.hpp"
#include <thread>

static const int STEP_DURATION_IN_MS = 1000;
static const int INITIAL_NUMBER_OF_PNJS_PER_WAVE = 5;

const int TIMED_GAME_INTERVAL = 2 * 60; // 2 minutes

class GameEngine {

private:
    GameState gameState; // The changing parts of the game
    Map map;  // The background

    int numStepsDone;
    int numOfPNJsPerWave;

    Timer timerSinceWaveStart;
    Timer timerSinceGameStart;


    PlayerState &getPlayerStateForWave(Wave &wave);

public:

    GameEngine(unsigned int mapSeed, std::string mode);

    bool update();

    GameState &getGameState();

    void createWaves();

    void updateWaves();

    void dealDamage(std::vector<Wave> &waves);

    void movePNJsInWaves(std::vector<Wave> &waves);

    void movePNJsInWave(Wave &wave);

    void removeDeadPNJsFromWaves();

    void updatePlayerStates();

    void addMoney();

    void dealDamageToBase();

    void giveGold(PlayerState &playerState);

    Wave &getWaveInSameQuadrant(AbstractTower &tower, std::vector<Wave> &waves);

    void increaseWaveDifficulty();

    std::string *serializeGameState();

    void addTower(AbstractTower * tower, int quadrant);

    void addPNJS(std::vector<Wave> &waves);

    void showMap();

    void giveKill(PlayerState &playerState);

    void checkIfGameIsOver();

    void declareWinner();

    void declareWinnerTeam();

    bool isGameFinished();

    void addKillToStat(PlayerState &playerState);

    void addPlayerState(int player_id);
    void addPlayerState(int player_id, int team);

    void deleteTower(Position& position, int& quadrant);

    void upgradeTower(Position &position, int &quadrant);

    void declareWinnerInClassicMode();

    void declareWinnerInTimedMode();
};


#endif //PROJET_GAMEENGINE_HPP
