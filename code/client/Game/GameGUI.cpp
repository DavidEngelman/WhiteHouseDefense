

#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QGroupBox>
#include "GameGUI.hpp"
    #include "../MapGUI.hpp"

GameGUI::GameGUI(unsigned seed, GameManager *manager) : AbstractGUI(nullptr), GameUI(seed, manager) {


    QHBoxLayout *mainLayout = new QHBoxLayout();
    QVBoxLayout* leftPanel = new QVBoxLayout;

    //* RIGHT PANEL //*
    /* Player Info */

    QVBoxLayout *actionLayout  = new QVBoxLayout; //tower shop + sell/upgrage + spells

    QString towerShopTitle = QString::fromStdString("Towers Shop");
    towerShop = new QGroupBox(towerShopTitle);
    displayTowerShop();
    actionLayout->addWidget(towerShop);


    QString deleteAndUpgradeTitle = QString::fromStdString("On Tower Actions");
    deleteAndUpgradeBox = new QGroupBox(deleteAndUpgradeTitle);
    displayDeleteAndUpgradeBox();
    actionLayout->addWidget(deleteAndUpgradeBox);


    QString spellBoxTitle = QString::fromStdString("Spells");
    spellBox = new QGroupBox(spellBoxTitle);
    displaySpellBox();
    actionLayout->addWidget(spellBox);

    //* LEFT PANEL //*
    /* Player Info */

    QFont font = QFont();
    font.setBold(true);
    font.setPointSize(30);

    usernameL = new QLabel;
    usernameL->setFont(font);

    font.setBold(false);
    font.setPixelSize(15);

    QString playerStatsBoxTitle = QString::fromStdString("Stats");
    playerStatsBox = new QGroupBox(playerStatsBoxTitle);

    QHBoxLayout *playerStateLayout = new QHBoxLayout;
    playerStateL = new QLabel;
    playerStateL->setFont(font);
    playerStateLayout->addWidget(playerStateL);
    playerStatsBox->setLayout(playerStateLayout);



    /* In Game Chat UI */
    QString chatBoxTitle = QString::fromStdString("Chat");
    chatBox = new QGroupBox(chatBoxTitle);
    inGameChatWidget = new InGameChatWidget(manager);

    QHBoxLayout *chatLayout = new QHBoxLayout;
    chatLayout->addWidget(inGameChatWidget);
    chatBox->setLayout(chatLayout);

    /* Set up left panel layout */
    leftPanel->addWidget(usernameL);
    leftPanel->addWidget(playerStatsBox);
    leftPanel->addWidget(chatBox);

    leftPanel->setAlignment(usernameL, Qt::AlignCenter|Qt::AlignTop);
    leftPanel->setAlignment(playerStateL, Qt::AlignCenter|Qt::AlignTop);
    leftPanel->setAlignment(inGameChatWidget, Qt::AlignCenter|Qt::AlignTop);

    /* Central Layout */
    QVBoxLayout *centralLayout  = new QVBoxLayout;
    setUpHealthBar();
    centralLayout->addWidget(baseHealthBar);
    centralLayout->addStretch();
    map = new MapGUI(seed, this, centralLayout);
    centralLayout->addStretch();

    otherPlayerHealthBarBox = new QGroupBox;
    setUpOtherPlayerHealthBar();
    centralLayout->addWidget(otherPlayerHealthBarBox);


    /* Main Layout */
    mainLayout->addLayout(leftPanel, 1);
    mainLayout->addLayout(centralLayout,1);
    mainLayout->addLayout(actionLayout, 1);


    this->setLayout(mainLayout);
    //playerInfo->setLayout(playerInfoLayout);

    this->showMaximized();

    // TODO: Pour l'instant, c'est la gameGUI qui declenche la fonction updatemap toutes les 10 msec
    // Je ne suis pas sur que ca devrait etre dans cette classe
    // Ca devrait probablement etre dans manager
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update_map()));
    timer->start(10);
}

Position GameGUI::getPosBuyingTower() {
    return Position();
}

void GameGUI::displayPlayersPlacingTowersMessage() {

}

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


Position GameGUI::getPosSellingTower() {
    return Position();
}

void GameGUI::display(GameState &gameState, int quadrant) {
    map->display(gameState, quadrant);
}

void GameGUI::displayTowerShop() {
    int scl = 10;
    QSize size = QSize(1400/scl, 1060/scl);
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

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(gunTowerB, 0, 0);
    layout->addWidget(sniperTowerB, 0, 1);
    layout->addWidget(shockTowerB, 1, 0);
    towerShop->setLayout(layout);

    QObject::connect(gunTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
    QObject::connect(sniperTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
    QObject::connect(shockTowerB, SIGNAL(clicked(int)), this, SLOT(handleBuyingTower(int)));
}

void GameGUI::displayDeleteAndUpgradeBox() {

    int scl = 10;
    QSize size = QSize(1400/scl, 1060/scl);

    deleteTowerB = new QPushButton;
    deleteTowerB->setEnabled(false);
    deleteTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/sell.png"));
    deleteTowerB->setIconSize(size);

    upgradeTowerB = new QPushButton;
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


void GameGUI::displaySpellBox() {
    int scl = 10;
    QSize size = QSize(1400/scl, 1060/scl);

    nukeB = new QPushButton;
    nukeB->setEnabled(false);
    nukeB->setIcon(QIcon("../../qt_ui/game_pictures/spells/trumpnuclear.png"));
    nukeB->setIconSize(size);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(nukeB, 0, 0);
    spellBox->setLayout(layout);

    QObject::connect(nukeB, SIGNAL(clicked()), this, SLOT(handleNukeSpell()));
}

void GameGUI::displayGameOver(GameState &gamestate) {

}

void GameGUI::displayPlayerInfos(GameState &gameState, int quadrant) {
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

void GameGUI::displayInfoForSupporter(GameState &gameState) {

}

void GameGUI::displayDeadMessage() {

}

void GameGUI::update_map() {
    manager->updateMap();
}

void GameGUI::disableTowerShop() {
    gunTowerB->setEnabled(false);
    sniperTowerB->setEnabled(false);
    shockTowerB->setEnabled(false);
}

void GameGUI::enableTowerShop() {
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
        default:
            manager->placeShockTower(map->getHighlightedPosition());
            break;
    }
    disableTowerShop();
}

void GameGUI::handleSellingTower() {
    manager->sellTower(map->getHighlightedPosition());
}

void GameGUI::handleUpgradingTower() {
    manager->upgradeTower(map->getHighlightedPosition());
}

void GameGUI::handleNukeSpell() {
    manager->nuclearBombSpell();
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

void GameGUI::updateHealthBar(int value) {
    baseHealthBar->setValue(value);
    baseHealthBar->setFormat("HP : " + QString::number(value) + "/100" );
}

void GameGUI::disableDeleteAndUpgradeBox() {
    upgradeTowerB->setEnabled(false);
    deleteTowerB->setEnabled(false);
}

void GameGUI::enableDeleteAndUpgradeBox() {
    upgradeTowerB->setEnabled(true);
    deleteTowerB->setEnabled(true);
}

void GameGUI::setUpOtherPlayerHealthBar() {
    QHBoxLayout *layout = new QHBoxLayout;
    for(int i = 0; i < 3; i++) {
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

void GameGUI::updateOtherPlayerHealthBar(std::vector<PlayerState> &playerState, int quadrant) {
    int count = 0;
    for (int i = 0; i != playerState.size(); i++) {
        if (i != quadrant) {
            int value = playerState[i].getHp();
            otherPlayerHealthBar[count]->setValue(value);
            otherPlayerHealthBar[count]->setFormat(QString::fromStdString(playerState[i].getUsername()) + " :" + QString::number(value) + "/100" );
            count++;
        }
    }
}
