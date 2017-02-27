#include "FriendListManager.hpp"

FriendListManager::FriendListManager(int port, char* address, int id, std::string username, App* my_master_app):
        NetworkedManager(port, address, my_master_app), player_id(id), username(username),friendList(getRequestServer(GET_FRIENDLIST, username)),
        friendRequests(getRequestServer(GET_FRIEND_REQUESTS, username)), pendingInvitations(getRequestServer(GET_PENDING_INVITATIONS,username)){
};

void FriendListManager::run() {
    friendListUI.display();

    int choice = friendListUI.select();
    while ( choice!=8 ){
        if (choice == 1){
            friendListUI.displayFriendList(getRequestServer(GET_FRIENDLIST, username), "friends");
        }else if (choice == 2 ){
            friendListUI.displayFriendList(getRequestServer(GET_FRIEND_REQUESTS, username), "friend requests");
        }else if (choice == 3) {
            friendListUI.displayFriendList(getRequestServer(GET_PENDING_INVITATIONS,username), "pending");


        }else if (choice == 4) {
            std::cout<<"Send Friend Request to : ";
            std::string toAdd = friendListUI.askUsername();
            std::string error = request_validity(ADD_FRIEND, username, toAdd);
            if (error.size() == 0) {
                sendRequestServer(ADD_FRIEND, toAdd);
                std::cout << "Invitation Sent to " <<toAdd<< std::endl;
            }else{
                std::cout<<error<<std::endl;
            }

        }else if (choice == 5 ){
            std::cout<<"Remove Friend : ";
            std::string toRemove = friendListUI.askUsername();
            std::string error = request_validity(REMOVE_FRIEND, username, toRemove);
            if (error.size() == 0) {
                sendRequestServer(REMOVE_FRIEND, toRemove);
                std::cout << "Friend removed successfully, sorry it had to end this way" << std::endl;
            }else{
                std::cout << error << std::endl;
            }
        }else if (choice == 6){
            std::cout<< "accept Friend : ";
            std::string toAccept = friendListUI.askUsername();
            std::string error = request_validity(ACCEPT_FRIEND_REQUEST, username, toAccept);
            if (error.size() == 0) {
                sendRequestServer(ACCEPT_FRIEND_REQUEST, toAccept);
                std::cout << "Friend request accepted, " <<toAccept<<" is now your friend !"<<std::endl;
            }else{
                std::cout << error << std::endl;
            }
        }else if (choice == 7) {
            std::cout << "decline Friend : ";
            std::string toDecline = friendListUI.askUsername();
            std::string error = request_validity(DECLINE_FRIEND_REQUEST, username, toDecline);
            if (error.size() == 0) {
                sendRequestServer(DECLINE_FRIEND_REQUEST, toDecline);
                std::cout << "Friend request declined." << std::endl;
            }else{
                std::cout << error << std::endl;
            }
        }
        friendListUI.display();
        choice = friendListUI.select();

    }
    MainManager * mainManager = new MainManager(server_ip_address, player_id, username, master_app);
    master_app->transition(mainManager); // Permet de revenir au main menu , je ne sais pas si
                                                    // c'est le meilleur moyen pour faire ca
}

std::string FriendListManager::getRequestServer(std::string action, std::string username ){
    std::string message = action + username+ ";";
    send_message(server_socket, message.c_str());
    char buffer[MAX_BUFF_SIZE];
    receive_message(server_socket, buffer);
    return std::string(buffer);
}

bool FriendListManager::sendRequestServer(std::string action, std::string otherUser){

    char server_response[10];
    std::string message = action + username + "," + otherUser+ ";" ;
    send_message(server_socket, message.c_str());
    receive_message(server_socket,server_response);
    return server_response[0] == '1';
}

std::string FriendListManager::request_validity(std::string request, std::string requester, std::string receiver) {
    updateFriendLists();
    if (request == ADD_FRIEND) {
        if (requester == receiver) {
            return "You can't add yourself";
        } else {
            if (getRequestServer("getProfileByUsername;", receiver).size() == 3 ) {
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
    }else if (request == ACCEPT_FRIEND_REQUEST || request == DECLINE_FRIEND_REQUEST) {
        if (!friendRequests.is_present(receiver)) {
            return "You have no invitation with that username";
        }
    }else if (request == REMOVE_FRIEND){
        if(!friendList.is_present(receiver)){
            return "You have no Friend with that username";
        }
    }
    return "";
}

void FriendListManager::updateFriendLists() {
    friendList.update(getRequestServer(GET_FRIENDLIST, username));
    friendRequests.update(getRequestServer(GET_FRIEND_REQUESTS,username));
    pendingInvitations.update(getRequestServer(GET_PENDING_INVITATIONS,username));
}