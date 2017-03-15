

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



void SpectatorGUI::display() {
    setUp();
    createTable();
    fillTable();

    QString s1 = "BACK TO MENU";
    QPushButton *backToMenuButton = new QPushButton(s1);
    backToMenuButton->setFixedSize(QSize(212,45));
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
    int i =0;
    for(GameInfo &elem : allGames) {

        gamesTable->insertRow( gamesTable->rowCount() );

        QString mode = QString::fromStdString(elem.getGameMode());
        QString playersNames = QString::fromStdString(fromVectToString(elem.getPlayers()));

        QTableWidgetItem *mode_item = new QTableWidgetItem(mode);
        mode_item->setForeground(QColor::fromRgb(244, 215, 66));

        QTableWidgetItem *playersName_item = new QTableWidgetItem(playersNames);
        playersName_item->setForeground(QColor::fromRgb(244, 215, 66));
        playersName_item->setTextAlignment(Qt::AlignCenter);


        ///JOIN BUTTON
        QWidget* pWidget = new QWidget();
        QPushButton *join_item = new QPushButton(join_string);
        join_item->setFixedSize(QSize(75,35));
        QHBoxLayout* pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(join_item);
        pLayout->setAlignment(Qt::AlignCenter);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pWidget->setLayout(pLayout);


        //QObject::connect(join_item, SIGNAL(clicked()), this, SLOT(popUp()));

        QSignalMapper* signalMapper = new QSignalMapper (this) ;
        connect (join_item, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
        signalMapper -> setMapping (join_item, i) ;
        connect (signalMapper, SIGNAL(mapped(int)), this, SLOT(gameSelection(int))) ;

        gamesTable->setItem(i,0,mode_item);
        gamesTable->setItem(i, 1, playersName_item);
        gamesTable->setCellWidget(i, 2, pWidget);

        i++;
    }

}

void SpectatorGUI::setUp() {
    this->setFixedHeight(600);
    this->setFixedWidth(1000);

    QPixmap bkgnd("../../qt_ui/game_pictures/backgrounds/supporter_bg.png");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

}

void SpectatorGUI::createTable() {

    setStyle();
    QFont font("calibri",16);

    gamesTable = new QTableWidget(this);
    gamesTable->setFont(font);
    gamesTable->setColumnCount(3);
    gamesTable->setColumnWidth(1,TABLE_WIDTH_SIZE - 200);
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
    return  string;

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
    QFont font("calibri",12);
    selectPlayerWindow->setWindowTitle("Player selection");
    selectPlayerWindow->setFixedSize(200,200);
    selectPlayerWindow->move(this->width()/2, this->height()/2);
    selectPlayerWindow->setWindowModality(Qt::ApplicationModal);

    list = new QListWidget(selectPlayerWindow);
    list->setFont(font);
    connect(list, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(playerSelection_onClick(QListWidgetItem*)));

    layout->addWidget(list);
    setUpCheckBox(i);

}

void SpectatorGUI::setUpCheckBox(int i) {
    for(std::string &player : allGames[i].getPlayers()) {
        //selectPlayerWindow->setCheckBox(new QCheckBox(QString::fromStdString(player)));
        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(player), list);
    }
}

void SpectatorGUI::selectGameAndPlayerProcess() {
    display();

}

void SpectatorGUI::playerSelection_onClick(QListWidgetItem* item) {
    playerSelection(item->text().toUtf8().constData()); // convert QString to std::string
}

void SpectatorGUI::launchSupporterMode() {
    int gamePort = allGames[spectatorManager->getGameSelected()].getPort();
    spectatorManager->connectToGame(gamePort, spectatorManager->getPlayerSelected());

}

