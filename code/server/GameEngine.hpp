#ifndef PROJET_GAMEENGINE_HPP
#define PROJET_GAMEENGINE_HPP

#include "../common/GameState.hpp"
#include "Timer.h"
#include "../common/Direction.h"

#define STEP_DURATION 1000

class GameEngine {

private:
    GameState gameState;
    int numStepsDone;

    Timer timer;
public:

    GameEngine();

    void update();
    void move_pnj_forward(PNJ& pnj);
    void updateWaves();


    void updateWave(Wave &wave);

    void dealDamage(std::vector<Wave> &waves);

    void movePNJsInWaves(std::vector<Wave> &waves);

    void movePNJsInWave(Wave &wave);

    void removeDeadPNJs();


    Wave& getWaveInSameQuadrant(AbstractTower &tower, std::vector<Wave> &waves);
};


#endif //PROJET_GAMEENGINE_HPP
