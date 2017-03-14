

#include "RankingGUI.hpp"
#include <QDesktopWidget>
#include <QHeaderView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtCore/QFile>

#define TABLE_HEIGHT_SIZE 400
#define TABLE_WIDTH_SIZE 870

RankingGUI::RankingGUI(RankingManager *manager) : RankingUI(manager){}

void RankingGUI::display() {



    this->setFixedHeight(600);
    this->setFixedWidth(1000);


    QPixmap bkgnd("../../qt_ui/game_pictures/backgrounds/trump_background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    createTable();
}


void RankingGUI::createTable() {


    setStyleSheet("QTableWidget {background-color: rgba(0, 0, 0, 0);}"

                          "QHeaderView::section {background-color: grey;"
                          "color: white;"
                          "border: 10px solid grey;}"
                          "QPushButton {border: 2px solid darkbrown;"
                          "padding: 0 8px;"
                          "background-image : url(../../qt_ui/game_pictures/buttons/mainmenu.png);"
                          "font-family: verdana 14px; }"
                          "QPushButton:pressed {background-image : url(../../qt_ui/game_pictures/buttons/connectPressed.png);,}"

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

    QString s1 = "BACK TO MENU";
    QPushButton *backToMenuButton = new QPushButton(s1);
    backToMenuButton->setFixedSize(QSize(212,45));

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
        rank_item->setForeground(QColor::fromRgb(255, 255, 255));

        QTableWidgetItem *usr_item = new QTableWidgetItem(UsrName);
        usr_item->setForeground(QColor::fromRgb(255, 255, 255));

        QTableWidgetItem *victory_item = new QTableWidgetItem(victories);
        victory_item->setForeground(QColor::fromRgb(255, 255, 255));

        rankingTable->setItem(i,0,rank_item);
        rankingTable->setItem(i, 1, usr_item);
        rankingTable->setItem(i, 2, victory_item);

        i++;
    }
}

void RankingGUI::display(std::vector<RankingInfos>& ranking) {
    display();
    fillRanking(ranking);
    this->show();

}

void RankingGUI::goToMainMenu() {
    rankingManager->goToMainMenu();
}


