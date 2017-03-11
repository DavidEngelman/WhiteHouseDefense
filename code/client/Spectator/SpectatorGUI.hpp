

#ifndef PROJET_SPECTATORGUI_HPP
#define PROJET_SPECTATORGUI_HPP


#include "../Abstract/AbstractGUI.hpp"

class SpectatorManager;

class SpectatorGUI : public AbstractGUI {
private:
    SpectatorManager *manager;

public:
    SpectatorGUI(SpectatorManager *manager);
    void setupGUI();
};


#endif //PROJET_SPECTATORGUI_HPP
