

#include "RankingGUI.hpp"
#include "../Other/QHandPointerButton.hpp"


#define TABLE_HEIGHT_SIZE 400
#define TABLE_WIDTH_SIZE 870

RankingGUI::RankingGUI(RankingManager *manager, QWidget* _parent) : AbstractGUI(_parent), RankingUI(manager){}

void RankingGUI::setUp() {
    this->setFixedHeight(600);
    this->setFixedWidth(1000);

    setBackgroundFromPath("../../qt_ui/resources/backgrounds/trump_background.png");
    createTable();
}


void RankingGUI::createTable() {


    setStyleSheet("QTableWidget {background-color: rgba(0, 0, 0, 0);}"

                          "QHeaderView::section {background-color: grey;"
                          "color: rgba(244, 215, 66);"
                          "border: 10px solid grey;}"
                          "QPushButton {border: 2px solid darkbrown;"
                          "padding: 0 8px;"
                          "border-image:url(../../qt_ui/resources/buttons/mainmenu.png);"
                          "font-family: verdana 14px; }"
                          "QPushButton:pressed {border-image:url(../../qt_ui/resources/buttons/connectPressed.png);}"

    );

    QFont font("calibri",16);


    QVBoxLayout *layout = new QVBoxLayout;


    rankingTable = new QTableWidget(this);
    rankingTable->setFont(font);
    rankingTable->setColumnCount(3);
    rankingTable->setColumnWidth(1,TABLE_WIDTH_SIZE - 200);
    rankingHeader << "Rank" << "Username" << "Victories";
    rankingTable->setHorizontalHeaderLabels(rankingHeader);
    rankingTable->horizontalHeader()->setStretchLastSection(true);

    rankingTable->verticalHeader()->setVisible(false);
    rankingTable->setShowGrid(false);
    rankingTable->setCornerButtonEnabled(false);
    rankingTable->setDragEnabled(false);
    rankingTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    layout->addWidget(rankingTable);

    QPushButton *backToMenuButton = new QHandPointerButton("BACK TO MENU", 212, 45);
    QObject::connect(backToMenuButton, SIGNAL(clicked()), this, SLOT(goToMainMenu()));

    layout->addWidget(backToMenuButton);
    layout->setAlignment(backToMenuButton, Qt::AlignHCenter);

    this->setLayout(layout);


}

void RankingGUI::fillRanking(std::vector<RankingInfos> &ranking) {
    int i = 0;
    for(RankingInfos &elem : ranking) {
        rankingTable->insertRow( rankingTable->rowCount() );
        QString rank = QString::fromStdString(std::to_string(i+1));
        QString UsrName = QString::fromStdString(elem.username);
        QString victories = QString::fromStdString(std::to_string(elem.victories));

        QTableWidgetItem *rank_item = new QTableWidgetItem(rank);
        rank_item->setForeground(QColor::fromRgb(244, 215, 66));
        rank_item->setTextAlignment(Qt::AlignCenter);

        QTableWidgetItem *usr_item = new QTableWidgetItem(UsrName);
        usr_item->setTextAlignment(Qt::AlignVCenter);
        usr_item->setForeground(QColor::fromRgb(244, 215, 66));

        QTableWidgetItem *victory_item = new QTableWidgetItem(victories);
        victory_item->setForeground(QColor::fromRgb(244, 215, 66));
        victory_item->setTextAlignment(Qt::AlignCenter);

        rankingTable->setItem(i,0,rank_item);
        rankingTable->setItem(i, 1, usr_item);
        rankingTable->setItem(i, 2, victory_item);

        i++;
    }
}

void RankingGUI::display(std::vector<RankingInfos>& ranking) {
    setUp();
    fillRanking(ranking);
    this->show();

}

void RankingGUI::goToMainMenu() {
    rankingManager->goToMainMenu();
}


