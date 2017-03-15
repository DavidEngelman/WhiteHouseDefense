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

    void display(std::vector<GameInfo>& gamesInfos) override ;
    int gameSelection(int number_of_games_available) override ;
    void displaySorryMessage() override ;
    std::string playerSelection(GameInfo &game_info) override ;
};


#endif //PROJET_SPECTATORUI_HPP
