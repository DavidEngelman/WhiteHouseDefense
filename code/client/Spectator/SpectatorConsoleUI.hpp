//
//

#ifndef PROJET_SPECTATORUI_HPP
#define PROJET_SPECTATORUI_HPP

#include <vector>
#include "../Game/GameInfo.hpp"
#include "SpectatorUI.hpp"
#include "../Abstract/AbstractConsoleUI.hpp"

class SpectatorConsoleUI : public AbstractConsoleUI, public SpectatorUI {

public:
    SpectatorConsoleUI(SpectatorManager *spectatorManager);

    void selectGameAndPlayerProcess() override;

    void display() override ;
    void displaySorryMessage() override ;
    void gameSelection(int game_index) override ;
    void playerSelection(std::string player_name) override ;

    void gameSelection_input();

    void playerSelection_input(GameInfo &game_info);
};


#endif //PROJET_SPECTATORUI_HPP
