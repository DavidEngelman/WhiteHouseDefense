#include <string>
#include "Credentials.h"
#include "FriendList.hpp" //TODO

class Account {

private:

    Credentials creds; // username + password
	FriendList friendList;
	int nbOfVictories;
	int nbPnjKilled;

public:
	std::string getUsername();

	void setUsername(std::string username);

	FriendList getFriendList();

	void setFriendList(FriendList friendList);

	int getNbOfVictories();

	void setNbOfVictories(int nbOfVictories);

	int getNbPnjKilled();

	void setNbPnjKilled(int nbPnjKilled);

	std::string getPassword();

	void setPassword(std::string password);
};
