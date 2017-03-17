

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
    void goToMainMenu() { SpectatorUI::goToMainMenu(); };
    void selectPlayerForGame(int gameIndex) override;
    void handlePlayerSelection(QListWidgetItem *item);



public:

    SpectatorGUI(SpectatorManager *manager);

    void getGameAndPlayer() override;

    void displaySorryMessage() override ;


    void fillTable();
    void setUp();
    void setStyle();
    void createTable();

    std::string fromVectToString(std::vector<std::string> &players);

    void addPlayersToList(int game_index);
    void setUpSelectPlayerWindow(int game_index);
};


#endif //PROJET_SPECTATORGUI_HPP
