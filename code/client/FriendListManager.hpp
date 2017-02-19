#ifndef FRIENDLISTMANAGER_HPP
#define FRIENDLISTMANAGER_HPP
#define MAX_BUFF_SIZE 1000

#include "NetworkedManager.hpp"
#include "../common/Networking.h"
#include "string"
#include "FriendListUI.hpp"
#include "FriendList.hpp"

class FriendListManager: NetworkedManager {

private:
	FriendListUI friendListUI;
	//FriendList friendList;
	int player_id;

public:
    FriendListManager(int port, char* address, int id);
	bool sendFriendRequest(std::string toAdd);
	bool removeFriend(std::string toRemove);
    bool acceptFriendRequest(std::string toAccept);
    bool declineFriendRequest(std::string toDecline);
    bool exitFriendList();

    std::string getFriendList();
    std::string getFriendRequests();
    std::string getPendingInvitations();

    void friendListProcess();

};

#endif