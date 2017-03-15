

#ifndef PROJET_SPECTATORGUI_HPP
#define PROJET_SPECTATORGUI_HPP


#include "../Abstract/AbstractGUI.hpp"
#include "SpectatorManager.hpp"
#include "SpectatorUI.hpp"
#include <QTableWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QListWidget>
#include <vector>

class SpectatorGUI : public AbstractGUI, public SpectatorUI {
Q_OBJECT

private:
    QWidget *selectPlayerWindow;
    QListWidget* list;
    QVBoxLayout *layout;
    QTableWidget* gamesTable;
    QStringList header;

public slots:
    void goToMainMenu();
    void popUp(int i);
    void onJoinClick();
    void onPlayerSelection();


public:
    SpectatorGUI(SpectatorManager *manager);

    void selectGameAndPlayer() override;

    void display() override ;
    int gameSelection(int number_of_games_available) override ;
    void displaySorryMessage() override ;
    std::string playerSelection(GameInfo &game_info) override ;
    void fillTable();
    void setUp();
    void setStyle();
    void createTable();

    std::string fromVectToString(std::vector<std::string> &players);

    void setUpCheckBox(int i);

    void setUpSelectPlayerWindow(int i);
};


#endif //PROJET_SPECTATORGUI_HPP
