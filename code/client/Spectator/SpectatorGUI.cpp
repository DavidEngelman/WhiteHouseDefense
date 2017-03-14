

#include "SpectatorGUI.hpp"


SpectatorGUI::SpectatorGUI(SpectatorManager *manager) : SpectatorUI(manager) {}

SpectatorGUI::~SpectatorGUI() {
    close();
}

void SpectatorGUI::display(std::vector<GameInfo> &gamesInfos) {

}

int SpectatorGUI::gameSelection(int number_of_games_available) {
    return 0;
}

void SpectatorGUI::displaySorryMessage() {

}

std::string SpectatorGUI::playerSelection(GameInfo &game_info) {
    return std::__cxx11::string();
}
