#ifndef FRIENDLIST_HPP
#define FRIENDLIST_HPP

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>


class FriendList {

private:
	std::vector<std::string> friendlist;
public:
	FriendList(std::string friendlist);
	void update(std::string friendlist);
	bool is_present(std::string friendlist);
	std::vector<std::string> getFriendList();

};

#endif
