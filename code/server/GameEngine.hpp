#ifndef PROJET_GAMEENGINE_HPP
#define PROJET_GAMEENGINE_HPP

#include "../common/GameState.hpp"
#include "Timer.h"
#include "../common/Direction.h"

static const int STEP_DURATION_IN_MS = 1000;
static const int INITIAL_NUMBER_OF_PNJS_PER_WAVE = 5;

class GameEngine {

private:
    GameState gameState; // The changing parts of the game
    Map map;  // The background

    int numStepsDone;
    int numOfPNJsPerWave;

    Timer timer;


    PlayerState &getPlayerStateForWave(Wave &wave);

public:

    GameEngine(unsigned int mapSeed);

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

    bool isGameFinished();

    std::string *serializeGameState();

    void addTower(AbstractTower * tower, int quadrant);

    void addPNJS(std::vector<Wave> &waves);

    void showMap();

    void giveKill(PlayerState &playerState);
};


#endif //PROJET_GAMEENGINE_HPP
