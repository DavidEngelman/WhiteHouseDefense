#include "FriendListUI.hpp"


void FriendListUI::display() {
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

void FriendListUI::displayFriendList(std::string friendlist, std::string command) {
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

std::string FriendListUI::askUsername() {
    std::string username;
    std::cin >> username;
    std::cout << std::endl;
    return username;
}

int FriendListUI::select() {
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