//
// Created by jepsiko on 09/03/17.
//

#ifndef FRIENDLISTGUI_HPP
#define FRIENDLISTGUI_HPP


#include "../Abstract/AbstractGUI.hpp"
#include "FriendListManager.hpp"
#include "FriendListUI.hpp"
#include "QTableWidget"
#include "QListWidget"
#include "QFormLayout"
#include "QPushButton"
#include "../other/QHandPointerButton.hpp"
#include <QScrollArea>
#include "QLabel"
#include "QLineEdit"
#include "QMessageBox"
#include "QGroupBox"
#include "QMenu"
#include "../Spectator/SpectatorManager.hpp"
#include <QHeaderView>
#include <QSignalMapper>
#include <QTimer>

class FriendListGUI : public AbstractGUI , public FriendListUI{
Q_OBJECT
public slots:
    void sendFriendRequest();
    void spectate(int index);
    void acceptFriend(int index);
    void declineFriend(int index);
    void removeFriend(int index);
    void refresh();

public:
    FriendListGUI(FriendListManager* manager, QWidget* _parent);
    virtual ~FriendListGUI();
    void display();
    void displayError();
    void setupFriendList();
    void setupFriendRequests();
    void setupPendingInvitations();

private:
    GameInfo& getGame(std::string username);
    int getStatus(std::string username);
    bool isInGame(std::string username);
    QTimer *updateTimer;
    QIcon iconsArray[3];
    QPushButton *addFriend;
    QLineEdit *toAdd;
    QTabWidget *tabWidget;
    QTableWidget* friendList;
    QTableWidget* friendRequests;
    QTableWidget* pendingInvitations;
    SpectatorManager *specManager;

};


#endif //PROJET_FRIENDLISTGUI_HPP
