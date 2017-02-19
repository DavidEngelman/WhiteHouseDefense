//
// Created by jurgen on 2/18/17.
//

#include "FriendListUI.hpp"


void FriendListUI::display() {
    /*Show user's menu*/
    std::cout << "   ======================================   " << std::endl;
    std::cout << "   |                                    |   " << std::endl;
    std::cout << "   |       1. My Friends                |   " << std::endl;
    std::cout << "   |       2. My FriendRequests         |   " << std::endl;
    std::cout << "   |       3. Add a new Friend          |   " << std::endl;
    std::cout << "   |       4. remove friend             |   " << std::endl;
    std::cout << "   |       5. accept friend             |   " << std::endl;
    std::cout << "   |       6. decline friend            |   " << std::endl;
    std::cout << "   |       7. exit                      |   " << std::endl;
    std::cout << "   ======================================   " << std::endl;


}
void FriendListUI::displayFriendList(std::string friendlist){
    std::string prettyList = " | ";
    int i = 0;
    while (i != friendlist.size()){
        if (friendlist[i] != ',') {
            prettyList += friendlist[i];
            i++;
        }else{
            prettyList += " | ";
            i++;
        }
    }
    std::cout<< prettyList + " | " << std::endl;
}
int FriendListUI::select(){
    /* Ask at the user his choice */
    int x = -1;
    std::cout << "   Enter your choice: ";
    std::cin >> x;
    while(std::cin.fail() or 0>x or x>7){
        display();
        std::cout << "   Error, enter a integer between 1 and 7" << std::endl;
        std::cout << "   Enter your choice: ";

        std::cin.clear();
        std::cin.ignore();
        std::cin >> x;
    }
    return x;
}