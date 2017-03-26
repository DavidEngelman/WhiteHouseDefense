

#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGroupBox>
#include "GameGUI.hpp"
#include "../Other/MapGUI.hpp"

GameGUI::GameGUI(bool isSupporter, unsigned seed, GameManager *manager) : AbstractGUI(nullptr),
                                                                          GameUI(isSupporter, seed, manager) {


    mainLayout = new QHBoxLayout();
    leftPanel = new QVBoxLayout;

    //* RIGHT PANEL //*
    /* Player Info */
    actionLayout = new QVBoxLayout; //tower shop + sell/upgrage + spells

    if (!isSupporter) {
        setUpTowerShop();
        setUpDeleteAndUpgradBox();
        setUpSpellsBox();
    } else {
        setUpSpellsBoxForSupporter();
    }

    //* LEFT PANEL //*
    /* Player Info */

    QString playerStatsBoxTitle = QString::fromStdString("Stats");
    playerStatsBox = new QGroupBox(playerStatsBoxTitle);


    setUpStatsBox();


    /* In Game Chat UI */
    QString chatBoxTitle = QString::fromStdString("Chat");
    chatBox = new QGroupBox(chatBoxTitle);
    inGameChatWidget = new InGameChatWidget(manager);

    QHBoxLayout *chatLayout = new QHBoxLayout;
    chatLayout->addWidget(inGameChatWidget);
    chatBox->setLayout(chatLayout);


    leftPanel->addWidget(chatBox);
    leftPanel->setAlignment(inGameChatWidget, Qt::AlignCenter | Qt::AlignTop);

    /* Central Layout */
    QVBoxLayout *centralLayout = new QVBoxLayout;
    setUpHealthBar();
    centralLayout->addWidget(baseHealthBar);
    centralLayout->addStretch();
    map = new MapGUI(seed, this, centralLayout);
    centralLayout->addStretch();

    QPixmap *adImage = new QPixmap("../../qt_ui/game_pictures/ads/steaks.jpg");
    QLabel *imageLabel = new QLabel();
    // MAYBE: DYNAMIC CAST??
    imageLabel->setScaledContents(true);
    imageLabel->setMaximumSize((static_cast<MapGUI *> (map))->width(), 80);
    imageLabel->setPixmap(*adImage);
    centralLayout->addWidget(imageLabel);

    otherPlayerHealthBarBox = new QGroupBox;
    setUpOtherPlayerHealthBar();
    centralLayout->addWidget(otherPlayerHealthBarBox);


    /* Main Layout */
    mainLayout->addLayout(leftPanel, 1);
    mainLayout->addLayout(centralLayout, 1);
    mainLayout->addLayout(actionLayout, 1);


    this->setLayout(mainLayout);
    //playerInfo->setLayout(playerInfoLayout);

    this->showMaximized();
//    this->showFullScreen();


}

void GameGUI::setUpTowerShop() {
    QString towerShopTitle = QString::fromStdString("Towers Shop");
    towerShop = new QGroupBox(towerShopTitle);
    displayTowerShop();
    actionLayout->addWidget(towerShop);
}


void GameGUI::setUpDeleteAndUpgradBox() {
    QString deleteAndUpgradeTitle = QString::fromStdString("On Tower Actions");
    deleteAndUpgradeBox = new QGroupBox(deleteAndUpgradeTitle);
    displayDeleteAndUpgradeBox();
    actionLayout->addWidget(deleteAndUpgradeBox);
}

void GameGUI::setUpSpellsBox() {
    QString spellBoxTitle = QString::fromStdString("Spells");
    spellBox = new QGroupBox(spellBoxTitle);
    displaySpellBox();
    actionLayout->addWidget(spellBox);
}

void GameGUI::setUpStatsBox() {
    QFont font = QFont();
    font.setBold(true);
    font.setPointSize(30);

    usernameL = new QLabel;
    usernameL->setFont(font);

    font.setBold(false);
    font.setPixelSize(15);

    QHBoxLayout *playerStateLayout = new QHBoxLayout;
    playerStateL = new QLabel;
    playerStateL->setFont(font);
    playerStateLayout->addWidget(playerStateL);
    playerStatsBox->setLayout(playerStateLayout);

    leftPanel->addWidget(usernameL);
    leftPanel->addWidget(playerStatsBox);

    leftPanel->setAlignment(usernameL, Qt::AlignCenter | Qt::AlignTop);
    leftPanel->setAlignment(playerStateL, Qt::AlignCenter | Qt::AlignTop);
}


Position GameGUI::getPosBuyingTower() {
    return Position();
}

void GameGUI::displayPlayersPlacingTowersMessage() {

}

///HEALTH BARS
void GameGUI::setUpHealthBar() {
    baseHealthBar = new QProgressBar;
    baseHealthBar->setStyleSheet(QString("QProgressBar {color: black}"));
    baseHealthBar->setMaximum(PLAYER_STARTING_HP);
    baseHealthBar->setMinimum(0);
    QPalette p = baseHealthBar->palette();
    p.setColor(QPalette::Highlight, Qt::green);
    baseHealthBar->setPalette(p);
    baseHealthBar->setTextVisible(true);
}

void GameGUI::setUpOtherPlayerHealthBar() {
    QHBoxLayout *layout = new QHBoxLayout;
    for (int i = 0; i < 3; i++) {
        QProgressBar *healthBar = new QProgressBar;
        healthBar->setStyleSheet(QString("QProgressBar {color: black}"));
        healthBar->setMaximum(PLAYER_STARTING_HP);
        healthBar->setMinimum(0);
        QPalette p = healthBar->palette();
        p.setColor(QPalette::Highlight, Qt::green);
        healthBar->setPalette(p);
        healthBar->setTextVisible(true);
        layout->addWidget(healthBar);
        otherPlayerHealthBar.push_back(healthBar);

    }

    otherPlayerHealthBarBox->setLayout(layout);
}

void GameGUI::updateHealthBar(int value) {
    baseHealthBar->setValue(value);
    baseHealthBar->setFormat("HP : " + QString::number(value) + "/" + QString::number(PLAYER_STARTING_HP));
}

void GameGUI::updateHealthBarOfSupportedPlayer(int value) {
    baseHealthBar->setValue(value);
    baseHealthBar->setFormat(
            "HP of Supported Player : " + QString::number(value) + "/" + QString::number(PLAYER_STARTING_HP));
}

void GameGUI::updateOtherPlayerHealthBar(std::vector<PlayerState> &playerState, int quadrant) {
    int count = 0;
    for (int i = 0; i != playerState.size(); i++) {
        if (i != quadrant) {
            int value = playerState[i].getHp();
            otherPlayerHealthBar[count]->setValue(value);
            otherPlayerHealthBar[count]->setFormat(QString::fromStdString(playerState[i].getUsername())
                                                   + " (" + QString::fromStdString(QUADRANT_NAMES[i]) + ")"
                                                   + " :" + QString::number(value) + "/"
                                                   + QString::number(PLAYER_STARTING_HP));
            count++;
        }
    }
}


Position GameGUI::getPosSellingTower() {
    return Position();
}

void GameGUI::display(GameState &gameState, int quadrant) {
    map->display(gameState, quadrant);
    displayPlayerInfos(gameState, quadrant);
}

void GameGUI::displayTowerShop() {
    int scl = 10;
    QSize size = QSize(1400 / scl, 1060 / scl);
    std::string tooltip;

    tooltip = "Tower that can attack one npc at the time\nwith a small range but with great damages\n";
    tooltip += "\nPrice : " + std::to_string(GUN_TOWER_PRICE) + " $";
    tooltip += "\nDamage : " + std::to_string(GUN_TOWER_DAMAGE);
    tooltip += "\nRange : " + std::to_string(GUN_TOWER_RANGE);

    gunTowerB = new QCustomButton(0);
    gunTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/guntower.png"));
    gunTowerB->setIconSize(size);
    gunTowerB->setToolTip(QString::fromStdString(tooltip));
    gunTowerB->setEnabled(false);

    tooltip = "Tower that can attack one npc at the time\nwith a great range but with small damages\n";
    tooltip += "\nPrice : " + std::to_string(SNIPER_TOWER_PRICE) + " $";
    tooltip += "\nDamage : " + std::to_string(SNIPER_TOWER_DAMAGE);
    tooltip += "\nRange : " + std::to_string(SNIPER_TOWER_RANGE);

    sniperTowerB = new QCustomButton(1);
    sniperTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/snipertower.png"));
    sniperTowerB->setIconSize(size);
    sniperTowerB->setToolTip(QString::fromStdString(tooltip));
    sniperTowerB->setEnabled(false);

    tooltip = "Tower that attack all the npc in it's range\nwith a small range and small damages\n";
    tooltip += "\nPrice : " + std::to_string(SHOCK_TOWER_PRICE) + " $";
    tooltip += "\nDamage : " + std::to_string(SHOCK_TOWER_DAMAGE);
    tooltip += "\nRange : " + std::to_string(SHOCK_TOWER_RANGE);

    shockTowerB = new QCustomButton(2);
    shockTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/shocktower.png"));
    shockTowerB->setIconSize(size);
    shockTowerB->setToolTip(QString::fromStdString(tooltip));
    shockTowerB->setEnabled(false);

    tooltip = "Tower that can attack one npc at the time\nbut deal zone damage around the npc\nwith a middle range and great damages\n";
    tooltip += "\nPrice : " + std::to_string(MISSILE_TOWER_PRICE) + " $";
    tooltip += "\nDamage : " + std::to_string(MISSILE_TOWER_DAMAGE);
    tooltip += "\nRange : " + std::to_string(MISSILE_TOWER_RANGE);
    tooltip += "\nSub Damage : " + std::to_string(MISSILE_TOWER_SUBDAMAGE);
    tooltip += "\nSub Range : " + std::to_string(MISSILE_TOWER_SUBRANGE);

    missileTowerB = new QCustomButton(3);
    missileTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/missiletower.png"));
    missileTowerB->setIconSize(size);
    missileTowerB->setToolTip(QString::fromStdString(tooltip));
    missileTowerB->setEnabled(false);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(gunTowerB, 0, 0);
    layout->addWidget(sniperTowerB, 0, 1);
    layout->addWidget(shockTowerB, 1, 0);
    layout->addWidget(missileTowerB, 1, 1);
    towerShop->setLayout(layout);

    QObject::connect(gunTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
    QObject::connect(sniperTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
    QObject::connect(shockTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
    QObject::connect(missileTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
}

void GameGUI::displayDeleteAndUpgradeBox() {

    int scl = 10;
    QSize size = QSize(1400 / scl, 1060 / scl);

    deleteTowerB = new QHandPointerButton;
    deleteTowerB->setEnabled(false);
    deleteTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/sell.png"));
    deleteTowerB->setIconSize(size);

    upgradeTowerB = new QHandPointerButton;
    upgradeTowerB->setEnabled(false);
    upgradeTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/upgrade.png"));
    upgradeTowerB->setIconSize(size);


    QGridLayout *layout = new QGridLayout;
    layout->addWidget(deleteTowerB, 0, 0);
    layout->addWidget(upgradeTowerB, 0, 1);
    deleteAndUpgradeBox->setLayout(layout);


    QObject::connect(deleteTowerB, SIGNAL(clicked()), this, SLOT(handleSellingTower()));
    QObject::connect(upgradeTowerB, SIGNAL(clicked()), this, SLOT(handleUpgradingTower()));


}

void GameGUI::disableTowerShop() {
    gunTowerB->setEnabled(false);
    sniperTowerB->setEnabled(false);
    shockTowerB->setEnabled(false);
    missileTowerB->setEnabled(false);
}

void GameGUI::enableTowerShop() {
    if (map->getHighlightedPosition() == Position(-1, -1)) { return; }

    int quadrant = manager->getQuadrant();
    if (map->computeQuadrant(map->getHighlightedPosition()) != quadrant) {
        disableTowerShop();
        disableDeleteAndUpgradeBox();
    } else {
        if (manager->isTowerInPosition(manager->getGameState(), map->getHighlightedPosition())) {
            disableTowerShop();
            enableDeleteAndUpgradeBox();
        } else {
            int playerMoney = manager->getGameState().getPlayerStates()[quadrant].getMoney();
            if (playerMoney > GUN_TOWER_PRICE) gunTowerB->setEnabled(true);
            if (playerMoney > SNIPER_TOWER_PRICE) sniperTowerB->setEnabled(true);
            if (playerMoney > SHOCK_TOWER_PRICE) shockTowerB->setEnabled(true);
            if (playerMoney > MISSILE_TOWER_PRICE) missileTowerB->setEnabled(true);
        }
    }
}

void GameGUI::handleBuyingTower(int typeOfTower) {
    switch (typeOfTower) {
        case 0:
            manager->placeGunTower(map->getHighlightedPosition());
            break;
        case 1:
            manager->placeSniperTower(map->getHighlightedPosition());
            break;
        case 2:
            manager->placeShockTower(map->getHighlightedPosition());
            break;
        default:
            manager->placeMissileTower(map->getHighlightedPosition());
            break;
    }
    disableTowerShop();
    enableDeleteAndUpgradeBox();
}

void GameGUI::handleSellingTower() {
    manager->sellTower(map->getHighlightedPosition());
}

void GameGUI::handleUpgradingTower() {
    manager->upgradeTower(map->getHighlightedPosition());
}


void GameGUI::displaySpellBox() {
    int scl = 10;
    QSize size = QSize(1400 / scl, 1060 / scl);

    nukeB = new QHandPointerButton;
    nukeB->setEnabled(false);
    nukeB->setIcon(QIcon("../../qt_ui/game_pictures/spells/trumpnuclear.png"));
    nukeB->setIconSize(size);

    freezeB = new QHandPointerButton;
    freezeB->setEnabled(false);
    freezeB->setIcon(QIcon("../../qt_ui/game_pictures/spells/frozentrump.png"));
    freezeB->setIconSize(size);

    airStrikeB = new QHandPointerButton;
    airStrikeB->setEnabled(false);
    airStrikeB->setIcon(QIcon("../../qt_ui/game_pictures/spells/airstrike.png"));
    airStrikeB->setIconSize(size);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nukeB, 0, 0);
    layout->addWidget(freezeB, 0, 1);
    layout->addWidget(airStrikeB, 1, 0);

    spellBox->setLayout(layout);

    QObject::connect(nukeB, SIGNAL(clicked()), this, SLOT(handleNukeSpell()));
    QObject::connect(freezeB, SIGNAL(clicked()), this, SLOT(handleFreezeSpell()));
    QObject::connect(airStrikeB, SIGNAL(clicked()), this, SLOT(handleAirStrike()));

}

void GameGUI::handleNukeSpell() {
    manager->nuclearBombSpell();
    playSound("../../qt_ui/game_pictures/sounds/explosion.mp3");
}

void GameGUI::handleFreezeSpell() {
    manager->launchFreezeSpell();
    playSound("../../qt_ui/game_pictures/sounds/freezeSpell.mp3");
}

void GameGUI::handleAirStrike() {
    int targetQuadrant = map->computeQuadrant(map->getHighlightedPosition());
    manager->launchAirStrike(targetQuadrant);
    playSound("../../qt_ui/game_pictures/sounds/airstrike.mp3");
}

void GameGUI::displayPlayerInfos(GameState &gameState, int quadrant) {
    if (!isSupporter()) {
        displayCurrentPlayerInfo(gameState, quadrant);
    } else {
        displayInfoForSupporter(gameState, quadrant);
    }
}

void GameGUI::displayCurrentPlayerInfo(GameState &gameState, int quadrant) {
    PlayerState playerState = gameState.getPlayerStates()[quadrant];
    std::string &text = playerState.getUsername();

    usernameL->setText(QString::fromStdString(text));
    usernameL->show();

    text = "Money : " + std::to_string(playerState.getMoney()) + " $";
    text += "\nHP : " + std::to_string(playerState.getHp());
    text += "\nNPC killed : " + std::to_string(playerState.getPnjKilled());
    text += "\nQuadrant : " + QUADRANT_NAMES[quadrant];

    playerStateL->setText(QString::fromStdString(text));
    playerStateL->show();

    updateHealthBar(playerState.getHp());
    updateOtherPlayerHealthBar(gameState.getPlayerStates(), quadrant);
}

void GameGUI::displayDeadMessage() {

}

void GameGUI::addChatMessage(const std::string &message, const std::string &sender) {
    inGameChatWidget->addChatMessage(message, sender);
}

void GameGUI::disableNukeSpell() {
    nukeB->setEnabled(false);
}

void GameGUI::enableNukeSpell() {
    nukeB->setEnabled(true);
}

void GameGUI::disableFreezeSpell() {
    freezeB->setEnabled(false);
}

void GameGUI::enableFreezeSpell() {
    freezeB->setEnabled(true);
}

void GameGUI::disableAirStrike() {
    airStrikeB->setEnabled(false);

}

void GameGUI::enableAirStrike() {
    if ((map->isEnemyBaseInHighlightedPosition(manager->getQuadrant())) && (manager->isAirStikeAvailable())) {
        std::cout << "Enabling air strike" << std::endl;
        airStrikeB->setEnabled(true);
    }

}

void GameGUI::enableSpells() {
    if (manager->isNukeSpellAvailable()) {
        enableNukeSpell();
    }
    if (manager->isFreezeSpellAvailable()) {
        enableFreezeSpell();
    }
}

void GameGUI::disableSpells() {
    if (manager->isNukeSpellAvailable()) {
        disableNukeSpell();
    }
    if (manager->isFreezeSpellAvailable()) {
        disableFreezeSpell();
    }
}

void GameGUI::disableDeleteAndUpgradeBox() {
    upgradeTowerB->setEnabled(false);
    deleteTowerB->setEnabled(false);
}

void GameGUI::enableDeleteAndUpgradeBox() {
    upgradeTowerB->setEnabled(true);
    deleteTowerB->setEnabled(true);
}


//////////// END OF GAME SCREEN PART //////////////////////

void GameGUI::displayGameOverAndStats(GameState &gamestate) {
    setUpEndOfGameLayout(gamestate);
    switchToEndGameDisplay();
}

void GameGUI::switchToEndGameDisplay() {
    this->hide();
    endofGameWidget = new QWidget;
    endofGameWidget->setLayout(endOfGameLayout);
    endofGameWidget->showMaximized();
}

void GameGUI::setUpEndOfGameLayout(GameState &gameState) {
    endOfGameLayout = new QVBoxLayout;
    setUpWinnerLooserBox(gameState);
    setUpStatsLayout(gameState);
    backToMenu = new QHandPointerButton(QString::fromStdString("Back to menu"));
    endOfGameLayout->addWidget(backToMenu);
    endOfGameLayout->setAlignment(backToMenu, Qt::AlignCenter);
    QObject::connect(backToMenu, SIGNAL(clicked()), this, SLOT(goToMenu()));

}

void GameGUI::setUpWinnerLooserBox(GameState &gameState) {
    winnerLoserInfos = new QGroupBox;
    QHBoxLayout *layout = new QHBoxLayout;
    QFont font = QFont();
    font.setBold(true);
    font.setPointSize(30);

    int myQuadrant = manager->getQuadrant();
    std::string info = bool_to_victory_defeat(gameState.getPlayerStates()[myQuadrant].getIsWinner());
    QLabel *label = new QLabel();
    label->setFont(font);
    if (!isSupporter()) {
        label->setText(QString::fromStdString(info));
        if (info == "Victory") label->setStyleSheet("QLabel { color : green; }");
        else label->setStyleSheet("QLabel { color : red; }");
    } else {
        label->setText("Winner: " + QString::fromStdString(manager->getWinner()));
    }

    layout->addWidget(label);

    layout->setAlignment(Qt::AlignCenter);
    winnerLoserInfos->setLayout(layout);
    endOfGameLayout->addWidget(winnerLoserInfos);

}

void GameGUI::setUpStatsLayout(GameState &gameState) {
    statsLayout = new QHBoxLayout;
    setUpChartBox(gameState);
    endOfGameLayout->addLayout(statsLayout);
}

void GameGUI::setUpChartBox(GameState &gameState) {

    chartBox = new QGroupBox;

    chartLayout = new QGridLayout;

    /////////CHART 1

    npcKilled = new QBarSet("NPC killed");

    for (PlayerState player : gameState.getPlayerStates()) {
        npcKilled->append(player.getNPCKilled());
    }

    QBarSeries *series = new QBarSeries();
    series->append(npcKilled);

    chart1 = new QChart();
    chart1->addSeries(series);
    chart1->setTitle("NPC killed");
    chart1->setAnimationOptions(QChart::SeriesAnimations);

    QStringList categories;
    for (PlayerState &player : gameState.getPlayerStates()) {
        categories.append(QString::fromStdString(player.getUsername()));
    }

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    axis->append(categories);
    chart1->createDefaultAxes();
    chart1->setAxisX(axis, series);
    chart1->legend()->setVisible(true);
    chart1->legend()->setAlignment(Qt::AlignBottom);

    chartView1 = new QChartView(chart1);
    chartView1->setRenderHint(QPainter::Antialiasing);

    chartLayout->addWidget(chartView1, 0, 0);


    /////////CHART 2

    nbTowersPlaced = new QBarSet("Towers placed");

    for (PlayerState player : gameState.getPlayerStates()) {
        nbTowersPlaced->append(player.getNbTowersPlaced());
    }

    nbTowersPlaced->setColor(QColor("green"));

    QBarSeries *series2 = new QBarSeries();
    series2->append(nbTowersPlaced);
    chart2 = new QChart();

    chart2->addSeries(series2);
    chart2->setTitle("Towers Placed");
    chart2->setAnimationOptions(QChart::SeriesAnimations);

    chart2->createDefaultAxes();
    QBarCategoryAxis *axis2 = new QBarCategoryAxis();
    axis2->append(categories);
    chart2->setAxisX(axis2, series2);
    chart2->legend()->setVisible(true);
    chart2->legend()->setAlignment(Qt::AlignBottom);


    chartView2 = new QChartView(chart2);
    chartView2->setRenderHint(QPainter::Antialiasing);

    chartLayout->addWidget(chartView2, 0, 1);


    /////CHART 3

    damageDealt = new QBarSet("Damage dealt");

    for (PlayerState player : gameState.getPlayerStates()) {
        damageDealt->append(player.getDamageDealt());
    }

    damageDealt->setColor(QColor("red"));

    QBarSeries *series3 = new QBarSeries();
    series3->append(damageDealt);

    chart3 = new QChart();
    chart3->addSeries(series3);
    chart3->setTitle("Damage Dealt");
    chart3->setAnimationOptions(QChart::SeriesAnimations);

    chart3->createDefaultAxes();
    QBarCategoryAxis *axis3 = new QBarCategoryAxis();
    axis3->append(categories);
    chart3->setAxisX(axis3, series3);
    chart3->legend()->setAlignment(Qt::AlignBottom);

    chartView3 = new QChartView(chart3);
    chartView3->setRenderHint(QPainter::Antialiasing);

    chartLayout->addWidget(chartView3, 1, 0);


    /////CHART 4

    moneySpend = new QBarSet("Money spend");

    for (PlayerState player : gameState.getPlayerStates()) {
        moneySpend->append(player.getMoneySpend());
    }

    moneySpend->setColor(QColor("orange"));

    QBarSeries *series4 = new QBarSeries();
    series4->append(moneySpend);

    chart4 = new QChart();
    chart4->addSeries(series4);
    chart4->setTitle("Money Spend");
    chart4->setAnimationOptions(QChart::SeriesAnimations);

    chart4->createDefaultAxes();
    QBarCategoryAxis *axis4 = new QBarCategoryAxis();
    axis4->append(categories);
    chart4->setAxisX(axis4, series4);
    chart4->legend()->setAlignment(Qt::AlignBottom);

    chartView4 = new QChartView(chart4);
    chartView4->setRenderHint(QPainter::Antialiasing);

    chartLayout->addWidget(chartView4, 1, 1);


    chartBox->setLayout(chartLayout);
    statsLayout->addWidget(chartBox);

}


//////////// SUPPORTER UI PART //////////////////////

void GameGUI::displayInfoForSupporter(GameState &gameState, int quadrant) {
    PlayerState playerSupported = gameState.getPlayerStates()[quadrant];
    std::string &playerSupportedUsrName = playerSupported.getUsername();

    usernameL->setText("You are Supporting " + QString::fromStdString(playerSupportedUsrName)
                       + " (" + QString::fromStdString(QUADRANT_NAMES[quadrant]) + ")");
    usernameL->show();

    std::string text;
    int i = 0;
    for (PlayerState &player : gameState.getPlayerStates()) {
        text += "Player : " + player.getUsername();
        text += "\nMoney : " + std::to_string(player.getMoney()) + " $";
        text += "\nHP : " + std::to_string(player.getHp());
        text += "\nNPC killed : " + std::to_string(player.getPnjKilled());
        text += "\nQuadrant : " + QUADRANT_NAMES[i] + "\n\n";
        i++;
    }

    playerStateL->setText(QString::fromStdString(text));
    playerStateL->show();

    updateHealthBarOfSupportedPlayer(playerSupported.getHp());
    updateOtherPlayerHealthBar(gameState.getPlayerStates(), quadrant);

}

void GameGUI::setUpSpellsBoxForSupporter() {
    supporterActionBox = new QGroupBox();
    displaySupporterActionBox();
    actionLayout->addWidget(supporterActionBox);
}

void GameGUI::displaySupporterActionBox() {
    int scl = 10;
    QSize size = QSize(1400 / scl, 1060 / scl);

    adSpellB = new QHandPointerButton;
    //TODO à changer par la bonne image
    adSpellB->setIcon(QIcon("../../qt_ui/game_pictures/towers/missiletower.png"));
    adSpellB->setIconSize(size);
    adSpellB->setEnabled(true);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(adSpellB, 0, 0);

    supporterActionBox->setLayout(layout);

    QObject::connect(adSpellB, SIGNAL(clicked()), this, SLOT(handleAdSpell()));

}

void GameGUI::handleAdSpell() {
    manager->launchAdSpell();
}

void GameGUI::adPopUp() {
    std::cout << "displaying popUp" << std::endl;
    QWidget *popUpWindow = new QWidget;
    popUpWindow->setFixedSize(500, 500);
    QVBoxLayout *adLayout = new QVBoxLayout;
    QLabel *adPictureLabel = new QLabel;
    adPictureLabel->setPixmap(QPixmap("../../qt_ui/game_pictures/ads/loreal.jpg"));
    adLayout->addWidget(adPictureLabel);
    popUpWindow->setLayout(adLayout);
    popUpWindow->show();
}

void GameGUI::goToMenu() {
    endofGameWidget->close();
    endofGameWidget->deleteLater();
    manager->comeBackToMenu();

}

void GameGUI::playSound(QString musicPath) {

    QMediaPlayer *mediaPlayer = new QMediaPlayer;
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl::fromLocalFile(QFileInfo(musicPath).absoluteFilePath()));

    mediaPlayer->setVolume(100);
    mediaPlayer->setPlaylist(playlist);
    mediaPlayer->play();
}