#ifndef PROJET_SPECTATORUI_H
#define PROJET_SPECTATORUI_H

#include "SpectatorManager.hpp"
#include "../Game/GameInfo.hpp"
#include "string"


class SpectatorManager;

/*
 * The sequences of calls will be:
 * 1) selectGameAndPlayer(), which calls getGameAndPlayer(). If there's no game, it calls displaySorryMessage()
 *                                                           and asks the manager to return to the main menu.
 * 2) selectPlayerForGame(int gameIndex)
 * 3) handlePlayerSelection(std::string playerName)
 *
 * This last function will call manager->connectToGame(gameInfo, selectedPlayer);
 */

class SpectatorUI : public virtual AbstractUI {

protected:
    SpectatorManager *spectatorManager;
    std::vector<GameInfo> *_games;
    GameInfo *selectedGame;
    std::string selectedPlayer;


public:
    SpectatorUI(SpectatorManager *spectatorManager) : spectatorManager(spectatorManager), selectedGame(nullptr) {};

    virtual void displayAndSelectGameAndPlayer(std::vector<GameInfo> *games);

    virtual void goToMainMenu();

    virtual void getGameAndPlayer() = 0;

    virtual void displaySorryMessage() = 0;

    virtual void selectPlayerForGame(int gameIndex) = 0;

    virtual void handlePlayerSelection(std::string &playerName);

    virtual ~SpectatorUI() = default;
};


#endif //PROJET_SPECTATORUI_H
