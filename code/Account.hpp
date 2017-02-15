#include <string>
#include "Credentials.h"
#include "FriendList.hpp" //TODO

class Account {

private:
	int id;
    Credentials creds; // username + password
	FriendList friendList;
	int nbOfVictories;
	int nbPnjKilled;

public:

	void setUsername(std::string username);

	void setPassword(std::string password);

	FriendList getFriendList() const;

	void setFriendList(FriendList friendList);

	int getNbOfVictories() const;

	void setNbOfVictories(int nbr);

	int getNbPnjKilled() const;

	void setNbPnjKilled(int nbr);

	void setId(int id);

	int getId() const;

	const Credentials &getCreds() const;
};
