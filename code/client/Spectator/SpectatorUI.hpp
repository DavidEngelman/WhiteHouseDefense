//
//

#ifndef PROJET_SPECTATORUI_H
#define PROJET_SPECTATORUI_H

#include "SpectatorManager.hpp"
#include "../Game/GameInfo.hpp"
#include "string"


class SpectatorManager;

class SpectatorUI: public virtual AbstractUI {

protected:
    SpectatorManager *spectatorManager;
    std::vector<GameInfo> allGames;

public:
    SpectatorUI(SpectatorManager *spectatorManager) : spectatorManager(spectatorManager) {};
    virtual void selectGameAndPlayer() = 0;
    virtual void display() = 0;
    virtual void displaySorryMessage() = 0;
    virtual void playerSelection(GameInfo &game_info) = 0;
    virtual void gameSelection(int number_of_games_available) = 0;
    void addGame(GameInfo &game) {
        SpectatorUI::allGames.push_back(game);
    }

    virtual ~SpectatorUI() = default;


};

#endif //PROJET_SPECTATORUI_H
