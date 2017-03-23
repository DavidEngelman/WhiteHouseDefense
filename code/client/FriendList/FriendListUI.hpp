#ifndef FRIENDLISTUI_HPP
#define FRIENDLISTUI_HPP

#include <iostream>
#include "FriendListManager.hpp"

class FriendListManager;

class FriendListUI : public virtual AbstractUI {
protected:
	FriendListManager* manager;
public:
	FriendListUI(FriendListManager* manager) : manager(manager) {};
	virtual ~FriendListUI() = default;
	virtual void display() = 0;
	virtual void displayError() = 0;
};



#endif

