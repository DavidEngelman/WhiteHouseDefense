#ifndef PROJET_MAINGUI_HPP
#define PROJET_MAINGUI_HPP

#include "../Abstract/AbstractGUI.hpp"
#include "MainUI.hpp"
#include "../Other/QCustomButton.hpp"
#include <QtWidgets/QLineEdit>
#include <QtCore/QSignalMapper>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include "../Other/InQueueWidget.hpp"

class MainGUI : public AbstractGUI, public MainUI {
    Q_OBJECT

private:
    QCustomButton *newGame;
    QCustomButton *spectator;
    QCustomButton *profile;
    QCustomButton *friendList;
    QCustomButton *leaderBoard;
    QCustomButton *settings;


    QCustomButton *classicMode;
    QCustomButton *timedMode;
    QCustomButton *teamMode;
    QWidget* dialog_game_mode_choice;

    QHBoxLayout* popup_h_layout;
    InQueueWidget* queueWidget;

public:
    MainGUI(MainManager *manager, QWidget* _parent);
    ~MainGUI() { close(); };
    void display() override;
    void displayGameModesMenu() override;
    void showInQueue() override;

public slots:
    void handleMenuChoice(int choice);
    void handleGameModeChoice(int choice);
    void leaveQueue();
};


#endif //PROJET_MAINGUI_HPP
