#include <iostream>
#include "GameState.hpp"
#include "../Other/Tools.hpp"
#include "../../server/Game/global.h"

GameState::GameState() : isGameOver(false) {}

GameState::GameState(std::string mode) : mode(mode), isGameOver(false) {}

std::string *GameState::serialize() {
    std::string *serialized_me = new std::string();

    *serialized_me += GAMESTATE_STRING + "!";

    *serialized_me += mode + "!";

    *serialized_me += bool_to_string(isGameOver) + "!";

    for (PlayerState &pstate: player_states) {
        *serialized_me += pstate.serialize();
    }

    *serialized_me += "!";

    mutex.lock();
    for (AbstractTower * tower: towers) {
        *serialized_me += tower->serialize();
    }
    mutex.unlock();

    *serialized_me += "!";

    for (Wave &wave: waves) {
        *serialized_me += wave.serialize();
    }

    *serialized_me += "!";

    return serialized_me;
}


int GameState::numPlayersAlive() {
    int number_of_players_alive = 0;
    for (PlayerState &ps: player_states) {
        if (ps.getHp() > 0) {
            number_of_players_alive++;
        }
    }
    return number_of_players_alive;
}


bool GameState::isRoundFinished() {
    for (Wave &wave: waves) {
        if (!wave.isComplete()) {
            return false;
        }
    }
    return true;
}

std::vector<Wave> &GameState::getWaves() {
    return waves;
}

std::vector<AbstractTower *> &GameState::getTowers() {
    return towers;
}

std::vector<PlayerState> &GameState::getPlayerStates() {
    return player_states;
}

void GameState::clearWaves() {
    waves.clear();
}

void GameState::addWave(Wave wave) {
    waves.push_back(wave);
}

bool GameState::getIsGameOver() const {
    return isGameOver;
}

bool GameState::isPlayerAlive(const int quadrant) {
    return player_states[quadrant].getHp() > 0;
}

void GameState::addTower(AbstractTower *tower, int quadrant) {
    player_states[quadrant].spendMoney(tower->getPrice());
    mutex.lock();
    towers.push_back(tower);
    mutex.unlock();
}

void GameState::deleteTower(Position &position, int quadrant) {
    std::vector<AbstractTower *>::iterator iter;
    for (iter = getTowers().begin(); iter != getTowers().end(); iter++) {
        if ((*iter)->getPosition() == position) {
            float amountPaidBack = (*iter)->getPrice() * PERCENTAGE_RECOVERED_MONEY;
            getPlayerStates()[quadrant].earnMoney((int) amountPaidBack);
            mutex.lock();
            towers.erase(iter);
            mutex.unlock();
            return;
        }
    }
}


bool GameState::upgradeTower(Position &position, int quadrant) {
    for (AbstractTower *tower : getTowers()) {
        if (tower->getPosition() == position) {
            float cost = (float) (tower->getPrice()) * (PERCENTAGE_RECOVERED_MONEY * (float) (tower->getLevel()));
            if (player_states[quadrant].getMoney() - cost >= 0) {
                if (!tower->upgrade())
                    return false;
                std::cout << "upgraded" << std::endl;
                player_states[quadrant].spendMoney((int) cost);
                getPlayerStates()[quadrant].incrMoneySpend(cost);
                return true;
            }
        }
    }

    return false;
}

/*
 * This special method is here to prevent segmentation faults.
 * This is only called in GameManager, because it deletes the towers from the heap.
 * In GUI mode, the MapGUI has a copy of the gameState, if we put the "delete tower" code in the destructor
 * the towers would be deleted twice (once in the destruction of the GameState of GameManager and
 * the second time in the destruction of the GameState of the MapGUI)
 */
void GameState::clearThingsInHeap() {
    for (AbstractTower *tower: towers) {
        delete tower;
    }

    for (Wave &wave: waves) {
        wave.destroy();
    }
}

void GameState::setIsGameOver(bool isGameOver) {
    GameState::isGameOver = isGameOver;
}

std::string &GameState::getMode() {
    return mode;
}

void GameState::addPlayerState(PlayerState &state) {
    player_states.push_back(state);
}

void GameState::setGameMode(std::string _mode) {
    mode = _mode;
}



