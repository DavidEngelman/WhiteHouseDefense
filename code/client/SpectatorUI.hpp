//
//

#ifndef PROJET_SPECTATORUI_HPP
#define PROJET_SPECTATORUI_HPP

#include <vector>
#include "GameInfo.h"

class SpectatorUI {

public:

    void displaySpectatorUI(std::vector<GameInfo>& gamesInfos);
    int inputSpectatorUI();
    void drawTitleGameType(std::string gameType);

};


#endif //PROJET_SPECTATORUI_HPP
