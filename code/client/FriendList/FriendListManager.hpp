#ifndef FRIENDLISTMANAGER_HPP
#define FRIENDLISTMANAGER_HPP
#define MAX_BUFF_SIZE 1000

 #include "../Other/NetworkedManager.hpp"
#include "../../common/Other/Networking.hpp"
#include "FriendList.hpp"
#include "../Main/MainManager.hpp"
#include <iostream>
#include "../../common/Other/Strings.hpp"
#include "FriendListUI.hpp"

class FriendListUI;

class FriendListManager: public NetworkedManager {

private:
	FriendListUI *friendListUI;
	FriendList friendList;
	FriendList friendRequests;
	FriendList pendingInvitations;


public:
	FriendListManager(int port, App* my_master_app);

	std::string getRequestServer(std::string action, std::string username);
	bool sendRequestServer(std::string action, std::string requester);
	std::string request_validity(std::string request, std::string requester, std::string optionalUser);
	void updateFriendLists();
	std::string getUsername();
	std::string getStatus(std::string username);
	FriendList getFriendList(){return friendList;};
	FriendList getFriendRequests(){return friendRequests;};
	FriendList getPendingInvitations(){return pendingInvitations;};

	void run() override;


};

#endif