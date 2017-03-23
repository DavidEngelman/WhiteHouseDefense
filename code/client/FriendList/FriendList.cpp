#include "FriendList.hpp"


FriendList::FriendList(std::string friendlist) {
    update(friendlist);
}

bool FriendList::is_present(std::string toFind) {
    return std::find(friendlist.begin(), friendlist.end(), toFind) != friendlist.end();
}

void FriendList::update(std::string friendstring) {
    friendlist.clear();
    std::istringstream ss(friendstring);
    std::string token;
    while (std::getline(ss, token, ',')) {
        friendlist.push_back(token);
    }

}

std::vector<std::string> FriendList::getFriendList() {
    return friendlist;
}








