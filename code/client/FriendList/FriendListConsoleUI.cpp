//
// Created by macbookair on 19/03/17.
//

#include "FriendListConsoleUI.h"
FriendListConsoleUI::FriendListConsoleUI(FriendListManager *manager) : FriendListUI(manager){}

void FriendListConsoleUI::displayMenu() {
    /*Show user's menu*/
    std::cout << "   ======================================   " << std::endl;
    std::cout << "   |       1. My Friends                |   " << std::endl;
    std::cout << "   |       2. My FriendRequests         |   " << std::endl;
    std::cout << "   |       3. Pending Invitations       |   " << std::endl;
    std::cout << "   |       4. Add a new Friend          |   " << std::endl;
    std::cout << "   |       5. remove friend             |   " << std::endl;
    std::cout << "   |       6. accept friend             |   " << std::endl;
    std::cout << "   |       7. decline friend            |   " << std::endl;
    std::cout << "   |       8. Return to Main menu       |   " << std::endl;
    std::cout << "   ======================================   " << std::endl;

}

void FriendListConsoleUI::display() {
    displayMenu();
    int choice = select();
    while (choice != 8) {
        if (choice == 1) {
            displayFriendList(manager->getRequestServer(GET_FRIENDLIST, manager->getUsername()), "friends");
        } else if (choice == 2) {
            displayFriendList(manager->getRequestServer(GET_FRIEND_REQUESTS,manager->getUsername()),
                              "friend requests");
        } else if (choice == 3) {
            displayFriendList(manager->getRequestServer(GET_PENDING_INVITATIONS,manager->getUsername()),
                              "pending");


        } else if (choice == 4) {
            std::cout << "Send Friend Request to : ";
            std::string toAdd = askUsername();
            std::string error = manager->request_validity(ADD_FRIEND, manager->getUsername(), toAdd);
            if (error.size() == 0) {
                manager->sendRequestServer(ADD_FRIEND, toAdd);
                std::cout << "Invitation Sent to " << toAdd << std::endl;
            } else {
                std::cout << error << std::endl;
            }

        } else if (choice == 5) {
            std::cout << "Remove Friend : ";
            std::string toRemove = askUsername();
            std::string error = manager->request_validity(REMOVE_FRIEND, manager->getUsername(), toRemove);
            if (error.size() == 0) {
                manager->sendRequestServer(REMOVE_FRIEND, toRemove);
                std::cout << "Friend removed successfully, sorry it had to end this way" << std::endl;
            } else {
                std::cout << error << std::endl;
            }
        } else if (choice == 6) {
            std::cout << "accept Friend : ";
            std::string toAccept = askUsername();
            std::string error = manager->request_validity(ACCEPT_FRIEND_REQUEST, manager->getUsername(), toAccept);
            if (error.size() == 0) {
                manager->sendRequestServer(ACCEPT_FRIEND_REQUEST, toAccept);
                std::cout << "Friend request accepted, " << toAccept << " is now your friend !" << std::endl;
            } else {
                std::cout << error << std::endl;
            }
        } else if (choice == 7) {
            std::cout << "decline Friend : ";
            std::string toDecline = askUsername();
            std::string error = manager->request_validity(DECLINE_FRIEND_REQUEST, manager->getUsername(), toDecline);
            if (error.size() == 0) {
                manager->sendRequestServer(DECLINE_FRIEND_REQUEST, toDecline);
                std::cout << "Friend request declined." << std::endl;
            } else {
                std::cout << error << std::endl;
            }
        }
        displayMenu();
        choice = select();

    }

}

void FriendListConsoleUI::displayError() {

}

void FriendListConsoleUI::displayFriendList(std::string friendlist, std::string command) {
    if (friendlist.size() == 0) {
        if (command == "pending") {
            std::cout << "You have no pending Invitation " << std::endl;
        } else {
            std::cout << "Sadly, you have no " << command << " :( " << std::endl;
        }
    } else {
        if (command == "pending") {
            std::cout << "Your pending Invitations :  ";
        } else if (command == "friends") {
            std::cout << "Your Friends  :  ";
        } else {
            std::cout << "Your Friend Requests : ";
        }
        std::string prettyList = " | ";
        int i = 0;
        while (i != friendlist.size()) {
            if (friendlist[i] != ',') {
                prettyList += friendlist[i];
                i++;
            } else {
                prettyList += " | ";
                i++;
            }
        }
        std::cout << prettyList + " | " << std::endl;
    }
}

std::string FriendListConsoleUI::askUsername() {
    std::string username;
    std::cin >> username;
    std::cout << std::endl;
    return username;
}

int FriendListConsoleUI::select() {
    /* Ask at the user his choice */
    int x = -1;
    std::cout << "   Enter your choice: ";
    std::cin >> x;
    while (std::cin.fail() or 0 > x or x > 8) {
        display();
        std::cout << "   Error, enter a integer between 1 and 8" << std::endl;
        std::cout << "   Enter your choice: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> x;
    }
    return x;
}