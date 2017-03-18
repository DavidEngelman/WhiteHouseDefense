

#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QTimer>
#include "GameGUI.hpp"

GameGUI::GameGUI(unsigned seed, GameManager *manager) : GameUI(seed, manager) {

    playerInfo = new QGroupBox(this);
    towerShop = new QGroupBox(this);
    QWidget *mapWidget = new QWidget(this);
    map = new MapGUI(seed, mapWidget);


    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(playerInfo, 1);
    layout->addWidget(mapWidget);
    layout->addWidget(towerShop, 1);

    mapWidget->setFixedSize(SIZE*TILES_SIZE, SIZE*TILES_SIZE);
    mapWidget->show();
    playerInfo->show();
    towerShop->show();
    this->setLayout(layout);
    this->showFullScreen();

    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(update_map()));
    timer->start(100);
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

void GameGUI::displayPosingPhase() {

}

void GameGUI::displayTowerShop() {
    int scl = 5;
    QSize size = QSize(1400/scl, 1060/scl);
    std::string tooltip;

    tooltip = "Tower that can attack one npc at the time\nwith a small range but with great damages\n";
    tooltip += "\nPrice : " + std::to_string(GUN_TOWER_PRICE) + " $";
    tooltip += "\nDamage : " + std::to_string(GUN_TOWER_DAMAGE);
    tooltip += "\nRange : " + std::to_string(GUN_TOWER_RANGE);

    gunTowerB = new QPushButton(towerShop);
    gunTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/guntower.png"));
    gunTowerB->setIconSize(size);
    gunTowerB->setToolTip(QString::fromStdString(tooltip));
    gunTowerB->setEnabled(false);
    gunTowerB->show();

    tooltip = "Tower that can attack one npc at the time\nwith a great range but with small damages\n";
    tooltip += "\nPrice : " + std::to_string(SNIPER_TOWER_PRICE) + " $";
    tooltip += "\nDamage : " + std::to_string(SNIPER_TOWER_DAMAGE);
    tooltip += "\nRange : " + std::to_string(SNIPER_TOWER_RANGE);

    sniperTowerB = new QPushButton(towerShop);
    sniperTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/snipertower.png"));
    sniperTowerB->setIconSize(size);
    sniperTowerB->setToolTip(QString::fromStdString(tooltip));
    sniperTowerB->setEnabled(false);
    sniperTowerB->show();

    tooltip = "Tower that attack all the npc in it's range\nwith a small range and small damages\n";
    tooltip += "\nPrice : " + std::to_string(SHOCK_TOWER_PRICE) + " $";
    tooltip += "\nDamage : " + std::to_string(SHOCK_TOWER_DAMAGE);
    tooltip += "\nRange : " + std::to_string(SHOCK_TOWER_RANGE);

    shockTowerB = new QPushButton(towerShop);
    shockTowerB->setIcon(QIcon("../../qt_ui/game_pictures/towers/shocktower.png"));
    shockTowerB->setIconSize(size);
    shockTowerB->setToolTip(QString::fromStdString(tooltip));
    shockTowerB->setEnabled(false);
    shockTowerB->show();

    QVBoxLayout *layout = new QVBoxLayout(towerShop);
    layout->addWidget(gunTowerB);
    layout->addWidget(sniperTowerB);
    layout->addWidget(shockTowerB);
    layout->addStretch();
}

void GameGUI::displayGameOver(GameState &gamestate) {

}

void GameGUI::displayPlayerInfos(GameState &gameState, int quadrant) {
    PlayerState playerState = gameState.getPlayerStates()[quadrant];
    std::string text = "\t" + playerState.getUsername();

    QFont font = QFont();
    font.setBold(true);
    font.setPointSize(30);

    usernameL = new QLabel(playerInfo);
    usernameL->setText(QString::fromStdString(text));
    usernameL->setAlignment(Qt::AlignHCenter);
    usernameL->setFont(font);
    usernameL->show();

    font.setBold(false);
    font.setPixelSize(15);

    text = "\n\n\n\tMoney : " + std::to_string(playerState.getMoney()) + " $";
    text += "\n\tHP : " + std::to_string(playerState.getHp());
    text += "\n\tNPC killed : " + std::to_string(playerState.getPnjKilled());
    text += "\n\tQuadrant : " + QUADRANT_NAMES[quadrant];

    playerStateL = new QLabel(playerInfo);
    playerStateL->setText(QString::fromStdString(text));
    playerStateL->setFont(font);
    playerStateL->show();
}

void GameGUI::displayInfoForSupporter(GameState &gameState) {

}

void GameGUI::display_dead_message() {

}

void GameGUI::update_map() {
    manager->update_map();
}
