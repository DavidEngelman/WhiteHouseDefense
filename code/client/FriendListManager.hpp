#ifndef FRIENDLISTMANAGER_HPP
#define FRIENDLISTMANAGER_HPP
#define MAX_BUFF_SIZE 1000

#include "NetworkedManager.hpp"
#include "../common/Networking.h"
#include "FriendListUI.hpp"
#include "FriendList.hpp"
#include "MainManager.hpp"
#include <iostream>
#include "../common/Strings.hpp"

class FriendListManager: public NetworkedManager {

private:
    FriendList friendList;
    FriendList friendRequests;
    FriendList pendingInvitations;
	FriendListUI friendListUI;
	int player_id;
	std::string username;

public:
    FriendListManager(int port, char* address,int id, std::string username);

	std::string getRequestServer(std::string action, std::string username);
	bool sendRequestServer(std::string action, std::string requester);
    std::string request_validity(std::string request, std::string requester, std::string optionalUser);
    void updateFriendLists();
    void friendListProcess();

};

#endif