#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <vector>
#include "PlayerState.hpp"
#include "AbstractTower.hpp"
#include "PNJ.hpp"
#include "Map.hpp"
#include "Wave.h"
#include "../common/Strings.hpp"



const static std::vector<std::string> validModes = {CLASSIC_MODE, TEAM_MODE, TIMED_MODE};

class GameState {
private:

    std::vector<PlayerState> player_states;
    std::vector<AbstractTower> towers;
    std::vector<Wave> waves;

    std::string mode;

    Map map;
public:
    Map &getMap() const;

    std::vector<Wave> &getWaves();

    std::vector<AbstractTower> &getTowers();

    std::string serialize();

    bool is_only_one_alive();

    bool isFinished();

    void decrease_player_hp(PlayerState &player, int amount);

    void increase_player_hp(PlayerState &player, int amount);



    void add_tower(Position position);

    // Cette fonction aussi
    void updateGameState(int commands);

    // Par contre il faudra une fonction pour faire évoluer l'état du jeu lors d'une vague.
    // genre: void updateGameState(int timeEllaped);
    // ou tout simplement: void updateGameState();
    // où est cette classe comptabilise le temps écoulé et fait les calculs pour voir de combien
    // les mexicains ont avancé (entre autres)

    bool isWaveFinished();
};

#endif