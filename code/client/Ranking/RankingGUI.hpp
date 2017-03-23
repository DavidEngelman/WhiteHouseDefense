
#ifndef PROJET_RANKINGGUI_HPP
#define PROJET_RANKINGGUI_HPP


#include "../Abstract/AbstractGUI.hpp"
#include "../../common/Other/RankingInfos.hpp"
#include "RankingConsoleUI.hpp"
#include <QTableWidget>
#include <QtWidgets/QTableWidget>

#include "RankingManager.hpp"
#include "RankingUI.hpp"


class RankingGUI : public AbstractGUI, public RankingUI {

    Q_OBJECT

public slots:
    void goToMainMenu();

private:
    QTableWidget* rankingTable;
    QStringList rankingHeader;
    RankingManager *manager;




public:
    RankingGUI(RankingManager *manager, QWidget* _parent);
    void setUp();
    void fillRanking(std::vector<RankingInfos>& ranking);
    void display(std::vector<RankingInfos>& ranking) override ;
    void createTable();
};


#endif //PROJET_RANKINGGUI_HPP
