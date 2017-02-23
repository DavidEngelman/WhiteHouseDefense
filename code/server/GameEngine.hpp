

#ifndef PROJET_GAMEENGINE_HPP
#define PROJET_GAMEENGINE_HPP

#include "../common/GameState.hpp"
#include "Timer.h"
#include "../common/Direction.h"

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

    void dealDamage(std::vector<Wave> &waves);

    void movePNJsInWaves(std::vector<Wave> &waves);

    void movePNJsInWave(Wave &wave);

    bool can_go_forward(int wave_id, Position &current_pos);

    bool can_go_left(int wave_id, Position &current_pos, Position &last_pos);

    bool can_go_right(int wave_id, Position &current_pos, Position &last_pos);

    Direction get_forward_direction(int wave_id);

    Direction get_right_direction(int wave_id);

    Direction get_left_direction(int wave_id);

    Wave& getWaveInSameQuadrant(AbstractTower &tower, std::vector<Wave> &waves);
};


#endif //PROJET_GAMEENGINE_HPP
