#include <string>

class FriendList {

private:
	std::string friends;

public:
	void addFriend(std::string username);

	void removeFriend(std::string username);
};
