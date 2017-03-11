
#ifndef PROJET_RANKINGGUI_HPP
#define PROJET_RANKINGGUI_HPP


#include "../Abstract/AbstractGUI.hpp"
#include "../../common/RankingInfos.h"
#include <QTableWidget>

class RankingManager;

class RankingGUI : public AbstractGUI {

    Q_OBJECT

private:
    QTableWidget* rankingTable;
    QStringList rankingHeader;
    RankingManager *manager;

public:
    RankingGUI(RankingManager *manager);
    void setupGUI() override;
    void fillRanking(std::vector<RankingInfos>& ranking);
    void display(std::vector<RankingInfos>& ranking);


    void createTable();
};


#endif //PROJET_RANKINGGUI_HPP
