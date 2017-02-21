#ifndef FRIENDLIST_HPP
#define FRIENDLIST_HPP

#include <string>

class FriendList {

private:
	std::string friends; // j'ai mis string pour l'instant sinon ca faisait chier pour un autre truc

public:
	FriendList(std::string friendlist);
	void printFriendList();
};

#endif
