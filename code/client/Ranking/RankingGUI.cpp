

#include "RankingGUI.hpp"
#include <QDesktopWidget>
#include <QHeaderView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>


RankingGUI::RankingGUI(RankingManager *manager) : rankingTable(NULL), manager(manager) {}

void RankingGUI::setupGUI() {
    createTable();
}


void RankingGUI::createTable() {


    setStyleSheet("QTableWidget {background-color: transparent ;}"
                          "QTableView{border : 2px solid gold}"
                          "QTableView{background-color: transparent;}"
                          "QHeaderView {background-color: gold;}"
    );

    QFont font("calibri",24);


    this->setFixedHeight(600);
    this->setFixedWidth(1000);

    QGridLayout *layout = new QGridLayout;

    QPixmap bkgnd("../../qt_ui/game_pictures/backgrounds/gold_ranking_bg.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);


    rankingTable = new QTableWidget(this);
    rankingTable->resize(400, rankingTable->height());
    rankingTable->resize(1000, rankingTable->width());
    rankingTable->setFont(font);
    rankingTable->setColumnCount(2);
    rankingHeader << "Username" << "Victories";
    rankingTable->setHorizontalHeaderLabels(rankingHeader);

    rankingTable->verticalHeader()->setVisible(true);
    rankingTable->setShowGrid(false);

    layout->addWidget(rankingTable, 200, 400, Qt::AlignCenter);
    this->setLayout(layout);

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


