#ifndef PROJET_MAINGUI_HPP
#define PROJET_MAINGUI_HPP

#include "../Abstract/AbstractGUI.hpp"
#include "MainUI.hpp"
#include "../QCustomButton.h"
#include <QtWidgets/QLineEdit>
#include <QtCore/QSignalMapper>

class MainGUI : public AbstractGUI, public MainUI {
    Q_OBJECT

private:
    QCustomButton *newGame;
    QCustomButton *spectator;
    QCustomButton *profile;
    QCustomButton *friendList;
    QCustomButton *leaderBoard;
    QCustomButton *exit;

public:
    MainGUI(MainManager *manager);
    ~MainGUI() { close(); };
    void display() override;
    void displayGameModesMenu() override;

    void handleGameModeChoice();

public slots:
    void handleMenuChoice(int choice);
};


#endif //PROJET_MAINGUI_HPP
