

#ifndef PROJET_GAMEENGINE_HPP
#define PROJET_GAMEENGINE_HPP

#include "../common/GameState.hpp"
#include "Timer.h"

class GameEngine {

private:

    GameState my_gamestate;
    Timer my_timer;


public:

    void update();


};


#endif //PROJET_GAMEENGINE_HPP
