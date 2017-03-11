

#include "RankingGUI.hpp"
#include <QDesktopWidget>
#include <QHeaderView>
#include <QtWidgets/QApplication>


RankingGUI::RankingGUI(RankingManager *manager) : rankingTable(NULL), manager(manager) {}

void RankingGUI::setupGUI() {
    createTable();
}


void RankingGUI::createTable() {
    rankingTable = new QTableWidget(this);
    rankingTable->setColumnCount(2);
    rankingHeader << "Username" << "Victories";
    rankingTable->setHorizontalHeaderLabels(rankingHeader);
    rankingTable->verticalHeader()->setVisible(true);
    rankingTable->setShowGrid(false);
    rankingTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    rankingTable->setGeometry(QApplication::desktop()->screenGeometry());
}

void RankingGUI::fillRanking(std::vector<RankingInfos> &ranking) {
    int i = 0;
    for(RankingInfos &elem : ranking) {
        rankingTable->insertRow( rankingTable->rowCount() );
        QString username = QString::fromStdString(elem.username);
        QString victories = QString::fromStdString(std::to_string(elem.victories));
        rankingTable->setItem(i, 0, new QTableWidgetItem(username));
        rankingTable->setItem(i, 1, new QTableWidgetItem(victories));
        i++;
    }
}

void RankingGUI::display(std::vector<RankingInfos>& ranking) {
    setupGUI();
    fillRanking(ranking);
    this->show();

}


