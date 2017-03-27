#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <vector>
#include "PlayerState.hpp"
#include "../Tower/AbstractTower.hpp"
#include "../Npc/PNJ.hpp"
#include "Wave.hpp"
#include "../Other/Strings.hpp"

class AbstractTower; // Ah, les dependences circulaires :(

/*
 *
 * Represents the changing parts of the game: the towers, the waves and NPCs, the player
 * states (money, life, ...).
 */
class GameState {
private:

    std::vector<PlayerState> player_states;
    std::vector<AbstractTower *> towers;
    std::vector<Wave> waves;
    bool isGameOver;

    std::string mode;


public:


    GameState();
    GameState(std::string mode);

    bool getIsGameOver() const;

    void setIsGameOver(bool isGameOver);

    std::string &getMode();

    std::vector<Wave> &getWaves();

    void addWave(Wave wave);

    void clearWaves();

    std::vector<AbstractTower *> &getTowers();

    void addTower(AbstractTower *tower, int quadrant);

    std::vector<PlayerState> &getPlayerStates();

    std::string * serialize();

    int numPlayersAlive();

    void setGameMode(std::string _mode);

    bool isRoundFinished();

    bool isPlayerAlive(const int quadrant);

    void addPlayerState(PlayerState &state);

    void deleteTower(Position &position, int quadrant);

    bool upgradeTower(Position &position, int quadrant);

    void clearThingsInHeap();
};

#endif