#ifndef PROJET_GAMEENGINE_HPP
#define PROJET_GAMEENGINE_HPP

#include "../common/GameState.hpp"
#include "Timer.hpp"
#include "../common/Direction.hpp"
#include <iostream>
#include "../common/AttackTower.hpp"
#include <thread>

class GameEngine {

private:
    GameState gameState; // The changing parts of the game
    Map map;  // The background

    int numStepsDone;
    int numOfPNJsPerWave;

    Timer timerSinceWaveStart;
    Timer timerSinceGameStart;


    PlayerState &getPlayerStateForWave(Wave &wave);

public:

    GameEngine(unsigned int mapSeed, std::string mode);

    Timer &getTimerSinceGameStart();

    bool update();

    GameState &getGameState();

    void createWaves();

    void updateWaves();

    void dealDamage(std::vector<Wave> &waves);

    void movePNJsInWaves(std::vector<Wave> &waves);

    void movePNJsInWave(Wave &wave);

    void removeDeadPNJsFromWaves();

    void updatePlayerStates();

    void addMoney();

    void dealDamageToBase();

    void giveGold(PlayerState &playerState);

    Wave &getWaveInSameQuadrant(AbstractTower &tower, std::vector<Wave> &waves);

    void increaseWaveDifficulty();

    std::string *serializeGameState();

    void addTower(AbstractTower * tower, int quadrant);

    void addPNJS(std::vector<Wave> &waves);

    void showMap();

    void giveKill(PlayerState &playerState);

    void checkIfGameIsOver();

    void declareWinner();

    void declareWinnerTeam();

    bool isGameFinished();

    void addKillToStat(PlayerState &playerState);

    void addPlayerState(int player_id, std::string username);
    void addPlayerState(int player_id, std::string username, int team);

    void deleteTower(Position& position, int& quadrant);

    void upgradeTower(Position &position, int &quadrant);

    void declareWinnerInClassicMode();

    void declareWinnerInTimedMode();

    void killAllNPC(int quadrant);
};


#endif //PROJET_GAMEENGINE_HPP
