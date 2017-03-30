

#include "SpectatorGUI.hpp"
#include "../Other/QHandPointerButton.hpp"

#define TABLE_WIDTH_SIZE 870


SpectatorGUI::SpectatorGUI(SpectatorManager *manager, QWidget* _parent) : AbstractGUI(_parent), SpectatorUI(manager),
                                                                          layout(new QVBoxLayout), selectPlayerWindow(new QWidget()) {}

void SpectatorGUI::getGameAndPlayer() {
    setUp();
    createTable();
    fillTable();

    /* Button to go back to Main Menu */
    QPushButton *backToMenuButton = new QHandPointerButton("BACK TO MENU", 212, 45);
    QObject::connect(backToMenuButton, SIGNAL(clicked()), this, SLOT(goToMainMenu()));
    layout->addWidget(backToMenuButton);
    layout->setAlignment(backToMenuButton, Qt::AlignHCenter);
    this->setLayout(layout);

    this->show();
}

void SpectatorGUI::displaySorryMessage() {
    QMessageBox::critical(this, "Sorry :(", "There is no game in progress");

}

void SpectatorGUI::fillTable() {
    QString join_string = "Join";
    int index = 0;
    for (GameInfo &elem : *_games) {

        gamesTable->insertRow(gamesTable->rowCount());

        QString mode = QString::fromStdString(elem.getGameMode());
        QString playerNames = QString::fromStdString(fromVectToString(elem.getPlayers()));

        QTableWidgetItem *modeTableItem = new QTableWidgetItem(mode);
        modeTableItem->setForeground(QColor::fromRgb(244, 215, 66));

        QTableWidgetItem *playerNameTableItem = new QTableWidgetItem(playerNames);
        playerNameTableItem->setForeground(QColor::fromRgb(244, 215, 66));
        playerNameTableItem->setTextAlignment(Qt::AlignCenter);

        /* Create join button */
        QWidget *buttonContainer = new QWidget();
        QPushButton *joinButton = new QHandPointerButton(join_string);
        joinButton->setFixedSize(QSize(75, 35));
        QHBoxLayout *buttonLayout = new QHBoxLayout(buttonContainer);
        buttonLayout->addWidget(joinButton);
        buttonLayout->setAlignment(Qt::AlignCenter);
        buttonLayout->setContentsMargins(0, 0, 0, 0);
        buttonContainer->setLayout(buttonLayout);

        /* Map button click to slot */
        QSignalMapper *signalMapper = new QSignalMapper(this);
        connect(joinButton, SIGNAL(clicked()), signalMapper, SLOT(map()));
        signalMapper->setMapping(joinButton, index);
        connect(signalMapper, SIGNAL(mapped(int)), this, SLOT(selectPlayerForGame(int)));

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
    setBackgroundFromPath("../../qt_ui/resources/backgrounds/supporter_bg.png");
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
                          "border-image:url(../../qt_ui/resources/buttons/gold_button_2.svg);"
                          "font-family: verdana 14px; }"
                          "QPushButton:pressed {background-image : url(../../qt_ui/resources/buttons/connectPressed.png);}"
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

void SpectatorGUI::selectPlayerForGame(int gameIndex) {
    selectedGame = &((*_games)[gameIndex]);
    setUpSelectPlayerWindow(gameIndex);
    selectPlayerWindow->show();
}

void SpectatorGUI::setUpSelectPlayerWindow(int game_index) {
    QVBoxLayout *layout = new QVBoxLayout(selectPlayerWindow);
    QFont font("calibri", 12);
    selectPlayerWindow->setWindowTitle("Player selection");
    selectPlayerWindow->setFixedSize(200, 200);
    selectPlayerWindow->move(this->width() / 2, this->height() / 2);
    selectPlayerWindow->setWindowModality(Qt::ApplicationModal);

    list = new QListWidget(selectPlayerWindow);
    list->setFont(font);
    connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem * )), this,
            SLOT(handlePlayerSelection(QListWidgetItem * )));

    layout->addWidget(list);
    addPlayersToList(game_index);
}

void SpectatorGUI::addPlayersToList(int game_index) {
    for (std::string &player : (*_games)[game_index].getPlayers()) {
        QListWidgetItem *item = new QListWidgetItem(QString::fromStdString(player), list);
    }
}

void SpectatorGUI::handlePlayerSelection(QListWidgetItem *item) {
    selectPlayerWindow->close();
    selectPlayerWindow->deleteLater();
    std::string playerName = item->text().toUtf8().toStdString();
    SpectatorUI::handlePlayerSelection(playerName);
}





