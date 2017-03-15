#ifndef PROJET_SPECTATORUI_HPP
#define PROJET_SPECTATORUI_HPP

#include <vector>
#include "../Game/GameInfo.hpp"
#include "SpectatorUI.hpp"
#include "../Abstract/AbstractConsoleUI.hpp"

class SpectatorConsoleUI : public AbstractConsoleUI, public SpectatorUI {

public:
    SpectatorConsoleUI(SpectatorManager *spectatorManager);

    void getGameAndPlayer() override;

    void displaySorryMessage() override;

    void selectPlayerForGame(int gameIndex) override;

    void displayCurrentGames();

    void showPlayersForCurrentGame();

    std::string askUserToSelectPlayer();
};


#endif //PROJET_SPECTATORUI_HPP
