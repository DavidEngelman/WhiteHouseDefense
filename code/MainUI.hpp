
#include <iostream>

class MainUI {


public:
	void display();
	
	void launchGame(int gameMode); // For example 0 means classic, 1 means against the time and 2 means with team
	void editProfil();
	void consultLeaderboard(int gameMode);
	/*void searchForFriend(String myFriend);
	void watchProfileOf(Account myFriend);
	void addFriend(Account newFriend);
	void deleteFriend(Account myFriend);
	void supportFriend(Account myFriend);*/
	
	void showWaitMessage();
};
