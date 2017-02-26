#include "GameState.hpp"

void GameState::DecreasePlayerHp(PlayerState &player, int amount) {
    player.decrease_hp(amount);
}

void GameState::IncreasePlayerHp(PlayerState &player, int amount) {
    player.decrease_hp(amount);
}

std::string* GameState::serialize() {
    std::string * serialized_me = new std::string();

    for (PlayerState &pstate: player_states) {
        // C'est un peu bizarre comme fonction. Intuitivement, on dirait qu'il va
        // mettre le resultat dans serialized_me, au lieu de faire un append.
        // C'est ce que j'ai pensé quand j'ai vu ça
        *serialized_me += pstate.serialize();
    }
    for (AbstractTower &tower: towers) {
        *serialized_me += tower.serialize();
    }
    for (Wave &wave: waves) {
        *serialized_me += wave.serialize();
    }

    return serialized_me;
}

//void GameState::addTower(AbstractTower tower) {
//    towers.push_back(tower);
//}

bool GameState::IsOnlyOneAlive() {
    int number_of_players_alive = 0;
    for (PlayerState &ps: player_states) {
        if (ps.getHp() > 0) {
            number_of_players_alive++;
        }
    }
    return (number_of_players_alive == 1);
}

int GameState::getWinnerClassic() {
    for (PlayerState &ps: player_states) {
        if (ps.getIsWinner()) {
            return ps.getPlayer_id(); //TODO peut etre changer avec le username
        }
    }

    return -1;
}

bool GameState::isRoundFinished() {
    for (Wave &wave: waves) {
        if ( !wave.isEmpty()) {
            return false;
        }
    }
    return true;
}

bool GameState::isFinished() {
    return IsOnlyOneAlive();
}



std::vector<Wave> &GameState::getWaves() {
    return waves;
}

std::vector<AbstractTower> &GameState::getTowers() {
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

