#ifndef FRIENDLISTMANAGER_HPP
#define FRIENDLISTMANAGER_HPP
#define MAX_BUFF_SIZE 1000

#include "../other/NetworkedManager.hpp"
#include "../../common/other/Networking.hpp"
#include "FriendList.hpp"
#include "../Main/MainManager.hpp"
#include <iostream>
#include "../../common/other/Strings.hpp"
#include "FriendListUI.hpp"

class FriendListUI;

class FriendListManager: public NetworkedManager {

private:
	FriendListUI *friendListUI;
	std::string username;
	FriendList friendList;
	FriendList friendRequests;
	FriendList pendingInvitations;
	int server_socketSpectate;


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
	bool isInGame(std::string username);

	void run() override;


};

#endif