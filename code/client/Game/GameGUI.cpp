

#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QTimer>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QGroupBox>
#include "GameGUI.hpp"
#include "../QCustomButton.h"
#include "../MapGUI.hpp"

GameGUI::GameGUI(unsigned seed, GameManager *manager) : GameUI(seed, manager) {

    playerInfo = new QGroupBox;
    QVBoxLayout* playerInfoLayout = new QVBoxLayout;
    QHBoxLayout *mainLayout = new QHBoxLayout();
    QVBoxLayout* leftPanel = new QVBoxLayout;

    msgBox.setText("Incorrect action");
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

    leftPanel->addWidget(usernameL);
    leftPanel->addWidget(playerStatsBox);
    leftPanel->addWidget(chatBox);

    leftPanel->setAlignment(usernameL, Qt::AlignCenter|Qt::AlignTop);
    leftPanel->setAlignment(playerStateL, Qt::AlignCenter|Qt::AlignTop);
    leftPanel->setAlignment(inGameChatWidget, Qt::AlignCenter|Qt::AlignTop);


    /* Main Layout */
    mainLayout->addLayout(leftPanel, 1);
    map = new MapGUI(seed, this, mainLayout);
    mainLayout->addLayout(actionLayout, 1);


    this->setLayout(mainLayout);
    //playerInfo->setLayout(playerInfoLayout);



    this->showFullScreen();

    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update_map()));
    timer->start(10);
}

Position GameGUI::getPosBuyingTower() {
    return Position();
}

void GameGUI::displayPlayersPlacingTowersMessage() {

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
    deleteTowerB->setEnabled(true);
    deleteTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/sell.png"));
    deleteTowerB->setIconSize(size);

    upgradeTowerB = new QPushButton;
    upgradeTowerB->setEnabled(true);
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
    int playerMoney = manager->getGameState().getPlayerStates()[manager->getQuadrant()].getMoney();
    if (playerMoney > GUN_TOWER_PRICE) gunTowerB->setEnabled(true);
    if (playerMoney > SNIPER_TOWER_PRICE) sniperTowerB->setEnabled(true);
    if (playerMoney > SHOCK_TOWER_PRICE) shockTowerB->setEnabled(true);
}



void GameGUI::handleBuyingTower(int typeOfTower) {

    switch (typeOfTower) {
        case 0:
            if (!manager->placeGunTower(map->getHighlightedPosition()))
                msgBox.show();
            break;
        case 1:
            if (!manager->placeSniperTower(map->getHighlightedPosition()));
                msgBox.show();
            break;
        default:
            if (!manager->placeShockTower(map->getHighlightedPosition()))
                 msgBox.show();
            break;
    }
    disableTowerShop();
}

void GameGUI::handleSellingTower() {

   if(!manager->sellTower(map->getHighlightedPosition()))
       msgBox.show();
}

void GameGUI::handleUpgradingTower() {

    if(!manager->upgradeTower(map->getHighlightedPosition()))
        msgBox.show();
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
