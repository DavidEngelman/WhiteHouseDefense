
#include "SpectatorUI.hpp"

void SpectatorUI::displayAndSelectGameAndPlayer(std::vector<GameInfo> *games) {
    _games = games;

    if (_games->size() == 0) {
        displaySorryMessage();
        goToMainMenu();
    } else {
        getGameAndPlayer();
    }
}

void SpectatorUI::goToMainMenu() { spectatorManager->goToMainMenu(); }

void SpectatorUI::handlePlayerSelection(std::string &playerName) {
    selectedPlayer = playerName;
    spectatorManager->connectToGame(*selectedGame, selectedPlayer);
}
