//
//

#ifndef PROJET_SPECTATORUI_HPP
#define PROJET_SPECTATORUI_HPP

#include <vector>
#include "GameInfo.h"

class SpectatorUI {

public:

    void displaySpectatorUI(std::vector<GameInfo>& gamesInfos);
    int inputSpectatorUI(int number_of_games_available);
    void drawTitleGameType(std::string gameType);
    void displaySorryMessage();

};


#endif //PROJET_SPECTATORUI_HPP