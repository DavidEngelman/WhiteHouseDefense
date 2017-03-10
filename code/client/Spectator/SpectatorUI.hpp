//
//

#ifndef PROJET_SPECTATORUI_HPP
#define PROJET_SPECTATORUI_HPP

#include <vector>
#include "../Game/GameInfo.hpp"
#include "../Abstract/AbstractUI.hpp"

class SpectatorUI : public AbstractUI {

public:

    void displaySpectatorUI(std::vector<GameInfo>& gamesInfos);
    int gameSelection(int number_of_games_available);
    void displaySorryMessage();

    std::string playerSelection(GameInfo &game_info);
};


#endif //PROJET_SPECTATORUI_HPP
