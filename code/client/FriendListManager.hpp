#ifndef FRIENDLISTMANAGER_HPP
#define FRIENDLISTMANAGER_HPP
#define MAX_BUFF_SIZE 1000

#include "NetworkedManager.hpp"
#include "../common/Networking.h"
#include "FriendListUI.hpp"
#include "FriendList.hpp"
#include "MainManager.hpp"
#include <iostream>


class FriendListManager: public NetworkedManager {

private:
	FriendListUI friendListUI;
	int player_id;

public:
    FriendListManager(int port, char* address, int id);
	bool sendFriendRequest(std::string toAdd);
	bool removeFriend(std::string toRemove);
    bool acceptFriendRequest(std::string toAccept);
    bool declineFriendRequest(std::string toDecline);

    std::string getFriendList();
    std::string getFriendRequests();
    std::string getPendingInvitations();

    void friendListProcess();
	void run() override;


};

#endif