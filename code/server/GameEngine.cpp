//
//

#include "GameEngine.hpp"

GameEngine::GameEngine() {
    my_timer.start();
}

void GameEngine::update() {/*TODO*/}

void GameEngine::move_pnj_forward(PNJ &pnj) {
    Position current_pos = pnj.getPosition();


}

void GameEngine::move_waves_forward() {
    my_gamestate.move_waves_forward();

}
