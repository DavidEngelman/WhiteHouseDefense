//
// Created by jurgen on 2/18/17.
//

#include "FriendListManager.hpp"

FriendListManager::FriendListManager(int port, char* address,int id, std::string username): NetworkedManager(port, address), player_id(id),username(username){
    friendListProcess();
};

void FriendListManager::friendListProcess() {
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
            if(sendRequestServer(ADD_FRIEND , toAdd)){
                std::cout<<"Invitation Sent"<<std::endl;
            };

        }else if (choice == 5 ){
            std::cout<<"Remove Friend : ";
            std::string toRemove = friendListUI.askUsername();
            if(sendRequestServer( REMOVE_FRIEND ,toRemove)){
                std::cout<<"Friend removed successfully"<<std::endl;
            };
        }else if (choice == 6){
            std::cout<< "accept Friend : ";
            std::string toAccept = friendListUI.askUsername();
            if (sendRequestServer( ACCEPT_FRIEND_REQUEST  ,toAccept)){
                std::cout<<"Friend request accepted"<<std::endl;
            };

        }else if (choice == 7) {
            std::cout << "decline Friend : ";
            std::string toDecline = friendListUI.askUsername();
            if (sendRequestServer( DECLINE_FRIEND_REQUEST ,toDecline)) {
                std::cout << "Friend request declined" << std::endl;
            };
        }
        friendListUI.display();
        choice = friendListUI.select();

    }
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

