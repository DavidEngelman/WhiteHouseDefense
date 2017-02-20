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
            friendListUI.displayFriendList(getRequestServer("getFriendList;", username), "friends");
        }else if (choice == 2 ){
            friendListUI.displayFriendList(getRequestServer("getFriendRequests;", username), "friend requests");
        }else if (choice == 3) {
            friendListUI.displayFriendList(getRequestServer("getPendingInvitations;",username), "pending");


        }else if (choice == 4) {
            std::cout<<"Send Friend Request to : ";
            std::string toAdd = friendListUI.askUsername();
            if(sendRequestServer("addFriend;" , toAdd)){
                std::cout<<"Invitation Sent"<<std::endl;
            };

        }else if (choice == 5 ){
            std::cout<<"Remove Friend : ";
            std::string toRemove = friendListUI.askUsername();
            if(sendRequestServer( "removeFriend;" ,toRemove)){
                std::cout<<"Friend removed successfully"<<std::endl;
            };
        }else if (choice == 6){
            std::cout<< "accept Friend : ";
            std::string toAccept = friendListUI.askUsername();
            if (sendRequestServer( "acceptFriendRequest;"  ,toAccept)){
                std::cout<<"Friend request accepted"<<std::endl;
            };

        }else if (choice == 7) {
            std::cout << "decline Friend : ";
            std::string toDecline = friendListUI.askUsername();
            if (sendRequestServer( "declineFriendRequest;" ,toDecline)) {
                std::cout << "Friend request declined" << std::endl;
            };
        }
        friendListUI.display();
        choice = friendListUI.select();

    }
    MainManager mainManager(ip_address, player_id, username); // Permet de revenir au main menu , je ne sais pas si
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
    if (server_response[0] == '1') {
        return true;
    }
    return false;
}

