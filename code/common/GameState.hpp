#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <vector>
#include "PlayerState.hpp"
#include "Tower.hpp"
#include "Wave.h"
#include "Map.hpp"

class GameState {

    std::vector<PlayerState> player_states;
    std::vector<Tower> towers;
    std::vector<Wave> waves;

    Map map;
public:

    bool is_only_one_alive();

    void decrease_player_hp(PlayerState &player, int amount);

    void increase_player_hp(PlayerState &player, int amount);

    void add_tower(Position position);

    // Oui, cette fonctio ne sert plus à grand chose. Je crois qu'on peut l'eliminer
    void applyChanges(std::string changes); //Pourquoi on a et ApplyChanges et UpdateGameState ?

    // Cette fonction aussi
    void updateGameState(int commands);

    // Par contre il faudra une fonction pour faire évoluer l'état du jeu lors d'une vague.
    // genre: void updateGameState(int timeEllaped);
    // ou tout simplement: void updateGameState();
    // où est cette classe comptabilise le temps écoulé et fait les calculs pour voir de combien
    // les mexicains ont avancé (entre autres)

    std::string serialize();
};

#endif