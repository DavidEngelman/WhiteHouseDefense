

#ifndef PROJET_GAMEENGINE_HPP
#define PROJET_GAMEENGINE_HPP

#include "../common/GameState.hpp"
#include "Timer.h"

class GameEngine {

private:

    GameEngine();

    GameState gameState;
    Timer my_timer;


public:

    void update();
    void move_pnj_forward(PNJ& pnj);
    void updateWaves();


    void updateWave(Wave &wave);
};


#endif //PROJET_GAMEENGINE_HPP
