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


public:
    SpectatorUI(SpectatorManager *spectatorManager) : spectatorManager(spectatorManager) {};
    virtual void display(std::vector<GameInfo>& gamesInfos) = 0;
    virtual void displaySorryMessage() = 0;
    virtual std::string playerSelection(GameInfo &game_info) = 0;
    virtual int gameSelection(int number_of_games_available) = 0;

    virtual ~SpectatorUI() = default;


};

#endif //PROJET_SPECTATORUI_H
