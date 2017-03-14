

#ifndef PROJET_SPECTATORGUI_HPP
#define PROJET_SPECTATORGUI_HPP


#include "../Abstract/AbstractGUI.hpp"
#include "SpectatorManager.hpp"
#include "SpectatorUI.hpp"

class SpectatorGUI : public AbstractGUI, public SpectatorUI {


public:
    SpectatorGUI(SpectatorManager *manager);
    void display(std::vector<GameInfo>& gamesInfos) override ;
    int gameSelection(int number_of_games_available) override ;
    void displaySorryMessage() override ;
    std::string playerSelection(GameInfo &game_info) override ;

    virtual ~SpectatorGUI();
};


#endif //PROJET_SPECTATORGUI_HPP
