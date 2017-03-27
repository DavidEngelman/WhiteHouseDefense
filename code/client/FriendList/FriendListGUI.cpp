
#include "FriendListGUI.hpp"


FriendListGUI::FriendListGUI(FriendListManager *manager, QWidget* _parent) : AbstractGUI(_parent), FriendListUI(manager) {
    specManager = new SpectatorManager(MATCHMAKER_SERVER_PORT, manager->getMasterApp());
    this->setWindowFlags(Qt::Window);
    iconsArray[0] = QIcon("../../qt_ui/game_pictures/icons/inGameIcon.png");
    iconsArray[1] = QIcon("../../qt_ui/game_pictures/icons/onlineIcon.png");
    iconsArray[2] = QIcon("../../qt_ui/game_pictures/icons/offlineIcon.png");
}


void FriendListGUI::display() {

    this->setFixedHeight(480);
    this->setFixedWidth(280);
    this->setBackgroundFromPath("../../qt_ui/game_pictures/backgrounds/bluebg.png", 1);
    setStylesheetFromPath("../../qt_ui/friendList.qss");
    QFont police("calibri");



    QFormLayout * fieldsLayout = new QFormLayout();

    tabWidget = new QTabWidget();
    tabWidget->setFixedHeight(400);


    toAdd = new QLineEdit();
    toAdd->setSelection(0, 16);
    toAdd->setFixedWidth(200);
    toAdd->setFixedHeight(40);
    toAdd->setAlignment(Qt::AlignHCenter);
    toAdd->setStyleSheet("QLineEdit,QLineEdit:hover{border-radius : 10px;border-style :solid ;border-color: gold ;border-width: 2px;background-image: url(../../qt_ui/game_pictures/backgrounds/goldBg.png);}");

    addFriend = new QHandPointerButton("", 50, 42);
    QObject::connect(addFriend, SIGNAL(clicked()), this, SLOT(sendFriendRequest()));

    fieldsLayout->addRow(tabWidget);
    fieldsLayout->addRow(toAdd,addFriend);
    fieldsLayout->setAlignment( Qt::AlignCenter);

    QFont font("calibri", 13);
    friendList = new QTableWidget();
    QHeaderView *horizontalHeader = friendList->horizontalHeader();
    QHeaderView *verticallHeader = friendList->verticalHeader();
    horizontalHeader->hide();
    verticallHeader->hide();
    friendList->setFont(font);
    friendList->setColumnCount(3);
    friendList->setColumnWidth(0,40);
    friendList->setColumnWidth(1,150);
    friendList->setColumnWidth(2,50);
    friendList->setShowGrid(false);
    friendList->setDragEnabled(false);

    friendRequests = new QTableWidget();
    QHeaderView *horizontalHeader2 = friendRequests->horizontalHeader();
    QHeaderView *verticallHeader2 = friendRequests->verticalHeader();
    horizontalHeader2->hide();
    verticallHeader2->hide();
    friendRequests->setFont(font);
    friendRequests->setColumnCount(3);
    friendRequests->setColumnWidth(0,40);
    friendRequests->setColumnWidth(1,150);
    friendRequests->setColumnWidth(2,50);
    friendRequests->setShowGrid(false);
    friendRequests->setDragEnabled(false);

    pendingInvitations = new QTableWidget();
    QHeaderView *horizontalHeader3 = pendingInvitations->horizontalHeader();
    QHeaderView *verticallHeader3 = pendingInvitations->verticalHeader();
    horizontalHeader3->hide();
    verticallHeader3->hide();
    pendingInvitations->setFont(font);
    pendingInvitations->setColumnCount(3);
    pendingInvitations->setColumnWidth(0,40);
    pendingInvitations->setColumnWidth(1,150);
    pendingInvitations->setColumnWidth(2,50);
    pendingInvitations->setShowGrid(false);
    pendingInvitations->setDragEnabled(false);

    setupFriendList();
    setupFriendRequests();
    setupPendingInvitations();

    tabWidget->addTab(friendList,tr("  Friends  "));
    tabWidget->addTab(friendRequests,tr(" Requests "));
    tabWidget->addTab(pendingInvitations,tr("  My Invitations  "));



    this->setLayout(fieldsLayout);

    updateTimer = new QTimer();
    QObject::connect(updateTimer, SIGNAL(timeout()), this, SLOT(refresh()));
    updateTimer->start(1000);


    this->show();
}

void FriendListGUI::sendFriendRequest() {
    std::string error = manager->request_validity(ADD_FRIEND, manager->getUsername(), toAdd->text().toStdString());
    if (error.size() == 0){
        std::cout<<manager->getStatus(toAdd->text().toStdString());
        manager->sendRequestServer(ADD_FRIEND, toAdd->text().toStdString());
        toAdd->setText("");
        refresh();
    }else{
        QMessageBox::critical(this, "Error", QString::fromStdString(error));
        toAdd->setText("");
        refresh();
    }
}



void FriendListGUI::setupFriendList() {

    FriendList _friends = manager->getFriendList();

    int index = 0;
    for(std::string _fr : _friends.getFriendList()){
        friendList->insertRow(friendList->rowCount());

        int status = getStatus(_fr);

        QTableWidgetItem *friendStatus = new QTableWidgetItem();

        friendStatus->setIcon(iconsArray[status]);

        QString QFriend = QString::fromStdString(_fr);
        QTableWidgetItem *friendItem = new QTableWidgetItem(QFriend);

        QWidget *buttonWidgets = new QWidget();

        QPushButton *spectateButton = new QHandPointerButton("");
        spectateButton->setFixedSize(20,20);
        if (status == 0) {
            spectateButton->setStyleSheet(
                    "QPushButton{ border-image: url(../../qt_ui/game_pictures/icons/spectateIcon.png) ;} QPushButton:pressed{ border-style :solid ;border-color: gold ;border-width : 0.5px;}");
            spectateButton->setFixedSize(QSize(20, 20));

            QSignalMapper *spectateMapper = new QSignalMapper(this);
            connect(spectateButton, SIGNAL(clicked()), spectateMapper, SLOT(map()));
            spectateMapper->setMapping(spectateButton, index);
            connect(spectateMapper, SIGNAL(mapped(int)), this, SLOT(spectate(int)));
        }else {
            spectateButton->setStyleSheet(
                    "QPushButton{ border-image: url(../../qt_ui/game_pictures/icons/spectateIconUnclickable.png); }");
            spectateButton->setFixedSize(QSize(20, 20));

        }

        QPushButton *deleteButton = new QHandPointerButton("");
        deleteButton->setFixedSize(20,20);
        deleteButton->setStyleSheet("QPushButton{ border-image: url(../../qt_ui/game_pictures/icons/deleteIcon.png) ;} QPushButton:pressed{ border-style :solid ;border-color: gold ;border-width : 0.5px;}");
        deleteButton->setFixedSize(QSize(20, 20));

        QHBoxLayout *buttonBox = new QHBoxLayout(buttonWidgets);
        buttonBox->addWidget(spectateButton);
        buttonBox->addWidget(deleteButton);
        buttonBox->setAlignment(Qt::AlignCenter);
        buttonBox->setContentsMargins(0, 0, 0, 0);
        buttonWidgets->setLayout(buttonBox);


        QSignalMapper *removeMapper = new QSignalMapper(this);
        connect(deleteButton, SIGNAL(clicked()), removeMapper, SLOT(map()));
        removeMapper->setMapping(deleteButton, index);
        connect(removeMapper, SIGNAL(mapped(int)), this, SLOT(removeFriend(int)));


        friendList->setItem(index, 0, friendStatus);
        friendList->setItem(index, 1, friendItem);
        friendList->setCellWidget(index, 2, buttonWidgets);
        index++;
    }
}

void FriendListGUI::setupFriendRequests() {

    FriendList _friendRequests = manager->getFriendRequests();

    int index = 0;
    for(std::string requests : _friendRequests.getFriendList()){
        friendRequests->insertRow(friendRequests->rowCount());

        int status = getStatus(requests);

        QTableWidgetItem *friendStatus = new QTableWidgetItem();

        friendStatus->setIcon(iconsArray[status]);


        QString QRequest = QString::fromStdString(requests);
        QTableWidgetItem *friendItem2 = new QTableWidgetItem(QRequest);

        QWidget *buttonWidgets2 = new QWidget();

        QPushButton *acceptButton = new QHandPointerButton("");
        acceptButton->setFixedSize(20,20);
        acceptButton->setStyleSheet("QPushButton{ border-image: url(../../qt_ui/game_pictures/icons/accept-128.png) ;} QPushButton:pressed{ border-style :solid ;border-color: gold ;border-width : 0.5px;}");
        acceptButton->setFixedSize(QSize(20, 20));

        QPushButton *declineButton = new QHandPointerButton("");
        declineButton->setFixedSize(20,20);
        declineButton->setStyleSheet("QPushButton{ border-image: url(../../qt_ui/game_pictures/icons/deleteIcon.png) ;} QPushButton:pressed{ border-style :solid ;border-color: gold ;border-width : 0.5px;}");
        declineButton->setFixedSize(QSize(20, 20));

        QHBoxLayout *buttonBox2 = new QHBoxLayout(buttonWidgets2);
        buttonBox2->addWidget(acceptButton);
        buttonBox2->addWidget(declineButton);
        buttonBox2->setAlignment(Qt::AlignCenter);
        buttonBox2->setContentsMargins(0, 0, 0, 0);
        buttonWidgets2->setLayout(buttonBox2);

        QSignalMapper *acceptMapper = new QSignalMapper(this);
        connect(acceptButton, SIGNAL(clicked()), acceptMapper, SLOT(map()));
        acceptMapper->setMapping(acceptButton, index);
        connect(acceptMapper, SIGNAL(mapped(int)), this, SLOT(acceptFriend(int)));

        QSignalMapper *declineMapper = new QSignalMapper(this);
        connect(declineButton, SIGNAL(clicked()), declineMapper, SLOT(map()));
        declineMapper->setMapping(declineButton, index);
        connect(declineMapper, SIGNAL(mapped(int)), this, SLOT(declineFriend(int)));



        friendRequests->setItem(index, 0, friendStatus);
        friendRequests->setItem(index, 1, friendItem2);
        friendRequests->setCellWidget(index, 2, buttonWidgets2);
        index++;
    }
}

void FriendListGUI::setupPendingInvitations() {


    FriendList _pendingInvitations = manager->getPendingInvitations();

    int index = 0;
    for(std::string invitation : _pendingInvitations.getFriendList()){
        pendingInvitations->insertRow(pendingInvitations->rowCount());

        int status = getStatus(invitation);

        QTableWidgetItem *friendStatus = new QTableWidgetItem();
        friendStatus->setIcon(iconsArray[status]);

        QString QFriend = QString::fromStdString(invitation);
        QTableWidgetItem *friendItem = new QTableWidgetItem(QFriend);

        QWidget *buttonWidgets = new QWidget();

        QPushButton *deleteButton = new QHandPointerButton("");
        deleteButton->setFixedSize(20,20);
        deleteButton->setStyleSheet("QPushButton{ border-image: url(../../qt_ui/game_pictures/icons/deleteIcon.png) ;} QPushButton:pressed{ border-style :solid ;border-color: gold ;border-width : 0.5px;}");
        deleteButton->setFixedSize(QSize(20, 20));

        QHBoxLayout *buttonBox = new QHBoxLayout(buttonWidgets);
        buttonBox->addWidget(deleteButton);
        buttonBox->setAlignment(Qt::AlignCenter);
        buttonBox->setContentsMargins(0, 0, 0, 0);
        buttonWidgets->setLayout(buttonBox);

        QSignalMapper *cancelMapper = new QSignalMapper(this);
        connect(deleteButton, SIGNAL(clicked()), cancelMapper, SLOT(map()));
        cancelMapper->setMapping(deleteButton, index);
        connect(cancelMapper, SIGNAL(mapped(int)), this, SLOT(cancelInvitation(int)));


        pendingInvitations->setItem(index, 0, friendStatus);
        pendingInvitations->setItem(index, 1, friendItem);
        pendingInvitations->setCellWidget(index, 2, buttonWidgets);
        index++;
    }

}

void FriendListGUI::spectate(int index) {
    std::string friendUsername = friendList->item(index,1)->text().toStdString();
    GameInfo gameInfo = getGame(friendUsername);
    specManager->connectToGame(gameInfo, friendUsername );
}

void FriendListGUI::acceptFriend(int index) {
    manager->sendRequestServer(ACCEPT_FRIEND_REQUEST,friendRequests->item(index,1)->text().toStdString());
    refresh();
}

void FriendListGUI::declineFriend(int index) {
    manager->sendRequestServer(DECLINE_FRIEND_REQUEST,friendRequests->item(index,1)->text().toStdString());
    refresh();

}

void FriendListGUI::removeFriend(int index) {
    manager->sendRequestServer(REMOVE_FRIEND,friendList->item(index,1)->text().toStdString());
    refresh();
}

void FriendListGUI::cancelInvitation(int index) {
    manager->sendRequestServer(CANCEL_INVITATION,pendingInvitations->item(index,1)->text().toStdString());
    refresh();
}

void FriendListGUI::refresh() {
    manager->updateFriendLists();
    friendList->setRowCount(0);
    friendRequests->setRowCount(0);
    pendingInvitations->setRowCount(0);
    setupFriendList();
    setupFriendRequests();
    setupPendingInvitations();
}

int FriendListGUI::getStatus(std::string username){
    if (manager->getStatus(username) == "1") {
        if (isInGame(username)){
            return 0;
        }else {
            return 1;
        }
    }else{
        return 2;
    }
}

bool FriendListGUI::isInGame(std::string username) {
    bool inGame = false;
    specManager->getGamesFromMatchMaker();
    std::vector<GameInfo> games = specManager->getGames();

    for (GameInfo &game : games){
        if (game.isInPlayers(username)){
            inGame = true;
            break;
        }
    }
    return inGame;
}

GameInfo FriendListGUI::getGame(std::string username){
    GameInfo friendGame;
    specManager->getGamesFromMatchMaker();
    std::vector<GameInfo> games = specManager->getGames();
    for (GameInfo &game : games){
        if (game.isInPlayers(username)){
            friendGame = game;
            break;
        }
    }
    return friendGame;
}

void FriendListGUI::displayError() {

}

FriendListGUI::~FriendListGUI(){

    close();

};