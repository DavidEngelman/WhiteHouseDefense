

#ifndef PROJET_GAMEENGINE_HPP
#define PROJET_GAMEENGINE_HPP

#include "../common/GameState.hpp"
#include "Timer.h"

class GameEngine {

private:

    GameEngine();

    GameState my_gamestate;
    Timer my_timer;


public:

    void update();
    void move_pnj_forward(PNJ& pnj);
    void move_all_pnj_forward();



};


#endif //PROJET_GAMEENGINE_HPP
