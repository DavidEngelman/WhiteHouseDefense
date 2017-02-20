//
// Created by jurgen on 2/18/17.
//

#include "FriendListManager.hpp"

FriendListManager::FriendListManager(int port, char* address, int id):
        NetworkedManager(port, address), player_id(id){}

void FriendListManager::friendListProcess() {
    friendListUI.display();

    int choice = friendListUI.select();
    while ( choice!=8 ){
        if (choice == 1){
            friendListUI.displayFriendList(getFriendList(), "friends");
        }else if (choice == 2 ){
            friendListUI.displayFriendList(getFriendRequests(), "friend requests");
        }else if (choice == 3) {
            friendListUI.displayFriendList(getPendingInvitations(), "pending");

        }else if (choice == 4) {
            std::cout<<"Send Friend Request to : ";
            std::string toAdd = friendListUI.askUsername();
            if(sendFriendRequest(toAdd)){
                std::cout<<"Invitation Sent"<<std::endl;
            };

        }else if (choice == 5 ){
            std::cout<<"Remove Friend : ";
            std::string toRemove = friendListUI.askUsername();
            if(removeFriend(toRemove)){
                std::cout<<"Friend removed successfully"<<std::endl;
            };
        }else if (choice == 6){
            std::cout<< "accept Friend : ";
            std::string toAccept = friendListUI.askUsername();
            if (acceptFriendRequest(toAccept)){
                std::cout<<"Friend request accepted"<<std::endl;
            };
        }else if (choice == 7) {
            std::cout << "decline Friend : ";
            std::string toDecline = friendListUI.askUsername();
            if (declineFriendRequest(toDecline)) {
                std::cout << "Friend request declined" << std::endl;
            };
        }
        friendListUI.display();
        choice = friendListUI.select();

    }
    MainManager mainManager(ip_address, player_id);
    my_master_app->transition(&mainManager);

}


std::string FriendListManager::getFriendList() {
    std::string message = "getFriendList;" + std::to_string(player_id)+ ";";
    send_message(server_socket, message.c_str());
    char buffer[MAX_BUFF_SIZE];
    receive_message(server_socket, buffer);
    return std::string(buffer);
}

std::string FriendListManager::getFriendRequests() {

    std::string message = "getFriendRequests;" + std::to_string(player_id)+ ";";
    send_message(server_socket, message.c_str());
    char buffer[MAX_BUFF_SIZE];
    receive_message(server_socket, buffer);
    return std::string(buffer);

}
std::string FriendListManager::getPendingInvitations() {
    std::string message = "getPendingInvitations;" + std::to_string(player_id)+ ";";
    send_message(server_socket, message.c_str());
    char buffer[MAX_BUFF_SIZE];
    receive_message(server_socket, buffer);
    return std::string(buffer);
}

bool FriendListManager::sendFriendRequest(std::string toAdd){

    char server_response[10];
    std::string message = "addFriend;"+ std::to_string(player_id) + "," + toAdd+ ";" ;
    send_message(server_socket, message.c_str());
    receive_message(server_socket,server_response);
    if (server_response[0] == '1') {
        return true;
    }
    return false;
}

bool FriendListManager::removeFriend(std::string toRemove) {

    char server_response[10];
    std::string message = "removeFriend;"+ std::to_string(player_id) + "," + toRemove+ ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket,server_response);
    if (server_response[0] == '1') {
        return true;
    }
    return false;

}
bool FriendListManager::acceptFriendRequest(std::string toAccept) {

    char server_response[10];
    std::string message = "acceptFriendRequest;"+ std::to_string(player_id) + "," + toAccept+ ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket,server_response);
    if (server_response[0] == '1') {
        return true;
    }
    return false;

}


bool FriendListManager::declineFriendRequest(std::string toDecline) {

    char server_response[10];
    std::string message = "declineFriendRequest;"+ std::to_string(player_id) + "," + toDecline+ ";";
    send_message(server_socket, message.c_str());
    receive_message(server_socket,server_response);
    if (server_response[0] == '1') {
        return true;
    }
    return false;

}

void FriendListManager::run() {
    friendListProcess();
}