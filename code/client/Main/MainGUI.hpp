#ifndef PROJET_MAINGUI_HPP
#define PROJET_MAINGUI_HPP

#include "../Abstract/AbstractGUI.hpp"
#include "MainUI.hpp"
#include "../QCustomButton.h"
#include <QtWidgets/QLineEdit>
#include <QtCore/QSignalMapper>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>

class MainGUI : public AbstractGUI, public MainUI {
    Q_OBJECT

private:
    QCustomButton *newGame;
    QCustomButton *spectator;
    QCustomButton *profile;
    QCustomButton *friendList;
    QCustomButton *leaderBoard;
    QCustomButton *classicMode;
    QCustomButton *timedMode;
    QCustomButton *teamMode;
    QCustomButton *cancel;
    QWidget* dialog_game_mode_choice;

    QHBoxLayout* popup_h_layout;
    QLabel* inQueueMessage;

public:
    MainGUI(MainManager *manager);
    ~MainGUI() { close(); };
    void display() override;
    void displayGameModesMenu() override;

public slots:
    void handleMenuChoice(int choice);
    void handleGameModeChoice(int choice);

    void showInQueue();
};


#endif //PROJET_MAINGUI_HPP
