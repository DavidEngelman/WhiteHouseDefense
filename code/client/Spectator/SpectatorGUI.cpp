

#include "SpectatorGUI.hpp"
#include <QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QAction>
#include <QtCore/QSignalMapper>
#include <QtWidgets/QListWidgetItem>

#define TABLE_WIDTH_SIZE 870


SpectatorGUI::SpectatorGUI(SpectatorManager *manager) : SpectatorUI(manager), layout(new QVBoxLayout),
                                                        selectPlayerWindow(new QWidget()) {}

void SpectatorGUI::selectGameAndPlayerProcess() {
    display();
}

void SpectatorGUI::display() {
    setUp();
    createTable();
    fillTable();

    QString s1 = "BACK TO MENU";
    QPushButton *backToMenuButton = new QPushButton(s1);
    backToMenuButton->setFixedSize(QSize(212, 45));
    QObject::connect(backToMenuButton, SIGNAL(clicked()), this, SLOT(goToMainMenu()));
    layout->addWidget(backToMenuButton);
    layout->setAlignment(backToMenuButton, Qt::AlignHCenter);

    this->setLayout(layout);

    this->show();

}

void SpectatorGUI::gameSelection(int game_index) {
    spectatorManager->setGameSelected(game_index);
    popUp(game_index);

}

void SpectatorGUI::playerSelection(std::string player_name) {
    spectatorManager->setPlayerSelected(player_name);
    launchSupporterMode();
}

void SpectatorGUI::displaySorryMessage() {
    //TODO

}

void SpectatorGUI::fillTable() {
    QString join_string = "Join";
    int index = 0;
    for (GameInfo &elem : allGames) {

        gamesTable->insertRow(gamesTable->rowCount());

        QString mode = QString::fromStdString(elem.getGameMode());
        QString playerNames = QString::fromStdString(fromVectToString(elem.getPlayers()));

        QTableWidgetItem *modeTableItem = new QTableWidgetItem(mode);
        modeTableItem->setForeground(QColor::fromRgb(255, 255, 255));

        QTableWidgetItem *playerNameTableItem = new QTableWidgetItem(playerNames);
        playerNameTableItem->setForeground(QColor::fromRgb(255, 255, 255));
        playerNameTableItem->setTextAlignment(Qt::AlignCenter);


        /* Create join button */
        QWidget *buttonContainer = new QWidget();
        QPushButton *joinButton = new QPushButton(join_string);
        joinButton->setFixedSize(QSize(75, 35));
        QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);
        buttonLayout->addWidget(joinButton);
        buttonLayout->setAlignment(Qt::AlignCenter);
        buttonLayout->setContentsMargins(0, 0, 0, 0);
        buttonContainer->setLayout(buttonLayout);


        //QObject::connect(join_item, SIGNAL(clicked()), this, SLOT(popUp()));

        /* Map button click to slot */
        QSignalMapper *signalMapper = new QSignalMapper(this);
        connect(joinButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(joinButton, index);
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(gameSelection(int)));

        /* Add elements to table */
        gamesTable->setItem(index, 0, modeTableItem);
        gamesTable->setItem(index, 1, playerNameTableItem);
        gamesTable->setCellWidget(index, 2, buttonContainer);

        index++;
    }

}

void SpectatorGUI::setUp() {
    this->setFixedHeight(600);
    this->setFixedWidth(1000);

    QPixmap bkgnd("../../qt_ui/game_pictures/backgrounds/trump_background.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

}

void SpectatorGUI::createTable() {
    setStyle();
    QFont font("calibri", 16);

    gamesTable = new QTableWidget(this);
    gamesTable->setFont(font);
    gamesTable->setColumnCount(3);
    gamesTable->setColumnWidth(1, TABLE_WIDTH_SIZE - 200);
    header << "Mode" << "Players" << "Join";
    gamesTable->setHorizontalHeaderLabels(header);
    gamesTable->horizontalHeader()->setStretchLastSection(true);
    gamesTable->verticalHeader()->setVisible(false);
    gamesTable->setShowGrid(false);
    gamesTable->setCornerButtonEnabled(false);
    gamesTable->setDragEnabled(false);
    gamesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    layout->addWidget(gamesTable);
}

void SpectatorGUI::setStyle() {
    setStyleSheet("QTableWidget {background-color: rgba(0, 0, 0, 0);}"
                          "QHeaderView::section {background-color: grey;"
                          "color: white;"
                          "border: 10px solid grey;}"
                          "QPushButton {border: 2px solid darkbrown;"
                          "padding: 0 8px;"
                          "border-image:url(../../qt_ui/game_pictures/buttons/gold_button_2.svg);"
                          "font-family: verdana 14px; }"
                          "QPushButton:pressed {background-image : url(../../qt_ui/game_pictures/buttons/connectPressed.png);}"
    );

}

std::string SpectatorGUI::fromVectToString(std::vector<std::string> &players) {
    std::string string = "";
    int i = 0;
    for (std::string &player : players) {
        string += player;
        if (i != players.size() - 1)
            string += " - ";
        i++;
    }
    return string;

}

void SpectatorGUI::goToMainMenu() {
    spectatorManager->goToMainMenu();
}

void SpectatorGUI::popUp(int i) {
    setUpSelectPlayerWindow(i);
    selectPlayerWindow->show();
}

void SpectatorGUI::setUpSelectPlayerWindow(int i) {
    QVBoxLayout *layout = new QVBoxLayout(selectPlayerWindow);
    QFont font("calibri", 12);
    selectPlayerWindow->setWindowTitle("Player selection");
    selectPlayerWindow->setFixedSize(200, 200);
    selectPlayerWindow->move(this->width() / 2, this->height() / 2);
    selectPlayerWindow->setWindowModality(Qt::ApplicationModal);

    list = new QListWidget(selectPlayerWindow);
    list->setFont(font);
    connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem * )), this,
            SLOT(playerSelection_onClick(QListWidgetItem * )));

    layout->addWidget(list);
    setUpCheckBox(i);

}

void SpectatorGUI::setUpCheckBox(int i) {
    for (std::string &player : allGames[i].getPlayers()) {
        //selectPlayerWindow->setCheckBox(new QCheckBox(QString::fromStdString(player)));
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(player), list);
    }
}

void SpectatorGUI::playerSelection_onClick(QListWidgetItem *item) {
    playerSelection(item->text().toUtf8().constData()); // convert QString to std::string
}

void SpectatorGUI::launchSupporterMode() {
    int gamePort = allGames[spectatorManager->getGameSelected()].getPort();
    spectatorManager->connectToGame(gamePort, spectatorManager->getPlayerSelected());

}

