#ifndef PROJET_GAMEENGINE_HPP
#define PROJET_GAMEENGINE_HPP

#include "../common/GameState.hpp"
#include "Timer.h"
#include "../common/Direction.h"

#define STEP_DURATION 1000
#define PNJ_DAMAGE 10

class GameEngine {

private:
    GameState gameState;
    int numStepsDone;
    int numOfPNJsPerWave;

    Timer timer;
public:

    GameEngine();

    bool update();


    void createWaves();
    void updateWaves();
    void dealDamage(std::vector<Wave> &waves);
    void movePNJsInWaves(std::vector<Wave> &waves);
    void movePNJsInWave(Wave &wave);
    void removeDeadPNJs();

    void updatePlayerStates();
    void dealDamageToBase(std::vector<PlayerState> &playerStates);


    Wave& getWaveInSameQuadrant(AbstractTower &tower, std::vector<Wave> &waves);

    void increaseWaveDifficulty();
};


#endif //PROJET_GAMEENGINE_HPP
