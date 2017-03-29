#include "FriendListManager.hpp"
#include "FriendListConsoleUI.h"
#include "FriendListGUI.hpp"

FriendListManager::FriendListManager(int port, App *my_master_app) :
        NetworkedManager(port, my_master_app), friendList(getRequestServer(GET_FRIENDLIST, master_app->getUsername())),
        friendRequests(getRequestServer(GET_FRIEND_REQUESTS, master_app->getUsername())),
        pendingInvitations(getRequestServer(GET_PENDING_INVITATIONS, master_app->getUsername()))
{
    master_app->setFriendListActive(true);
    if(isConsole){
        friendListUI = new FriendListConsoleUI(this);
    }else{
        friendListUI = new FriendListGUI(this, master_app->getMainWindow());
    }
}

void FriendListManager::run() {
    friendListUI->display();
}

std::string FriendListManager::getRequestServer(std::string action, std::string username) {
    std::string message = action + username + ";";
    send_message(server_socket, message.c_str());
    char buffer[MAX_BUFF_SIZE];
    receive_message(server_socket, buffer);
    return std::string(buffer);
}

bool FriendListManager::sendRequestServer(std::string action, std::string otherUser) {

    char server_response[10];
    std::string message = action + master_app->getUsername() + "," + otherUser + ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket, server_response);
    return server_response[0] == '1';
}

std::string FriendListManager::request_validity(std::string request, std::string requester, std::string receiver) {
    updateFriendLists();
    if (request == ADD_FRIEND) {
        if (requester == receiver) {
            return "You can't add yourself";
        } else {
            if (getRequestServer("getProfileByUsername;", receiver).size() == 5) {
                return "No Player was found with that username";
            } else {
                updateFriendLists();
                if (friendList.is_present(receiver)) {
                    return receiver + " is already your Friend";
                } else if (friendRequests.is_present(receiver)) {
                    return receiver + " already sent you an invitation";
                } else if (pendingInvitations.is_present(receiver)) {
                    return "You've already send an invitation to that user";
                }
            }
        }
    } else if (request == ACCEPT_FRIEND_REQUEST || request == DECLINE_FRIEND_REQUEST) {
        if (!friendRequests.is_present(receiver)) {
            return "You have no invitation with that username";
        }
    } else if (request == CANCEL_INVITATION){
        if (!pendingInvitations.is_present(receiver)){
            return "No request was sent to that user";
        }
    } else if (request == REMOVE_FRIEND) {
        if (!friendList.is_present(receiver)) {
            return "You have no Friend with that username";
        }
    }
    return "";
}

void FriendListManager::updateFriendLists() {
    friendList.update(getRequestServer(GET_FRIENDLIST, master_app->getUsername()));
    friendRequests.update(getRequestServer(GET_FRIEND_REQUESTS, master_app->getUsername()));
    pendingInvitations.update(getRequestServer(GET_PENDING_INVITATIONS, master_app->getUsername()));
}

std::string FriendListManager::getUsername() {
    return master_app->getUsername();
}

std::string FriendListManager::getStatus(std::string username) {
    return getRequestServer(GET_STATUS,username);
}

FriendListManager::~FriendListManager() {
    master_app->setFriendListActive(false);
    friendListUI->destroy();
}

void FriendListManager::goBackToMainMenu() {
    MainManager* mainManager = new MainManager(ACCOUNT_SERVER_PORT,master_app);
    master_app->transition(mainManager);

}

