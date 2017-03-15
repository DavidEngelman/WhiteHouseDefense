

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
    void gameSelection(int game_index) override ;
    void playerSelection_onClick(QListWidgetItem* item);



public:

    SpectatorGUI(SpectatorManager *manager);

    void selectGameAndPlayerProcess() override;

    void display() override ;
    void displaySorryMessage() override ;
    void fillTable();
    void setUp();
    void setStyle();
    void createTable();
    void popUp(int i);


    std::string fromVectToString(std::vector<std::string> &players);

    void setUpCheckBox(int i);

    void setUpSelectPlayerWindow(int i);

    void playerSelection(std::string player_name) override;

    void launchSupporterMode();
};


#endif //PROJET_SPECTATORGUI_HPP
