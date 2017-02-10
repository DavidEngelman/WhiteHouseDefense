class Account {

private:
	string username;
	string password;
	FriendList friendList;
	int nbOfVictories;
	int nbPnjKilled;

public:
	string getUsername();

	void setUsername(string username);

	FriendList getFriendList();

	void setFriendList(FriendList friendList);

	int getNbOfVictories();

	void setNbOfVictories(int nbOfVictories);

	int getNbPnjKilled();

	void setNbPnjKilled(int nbPnjKilled);

	string getPassword();

	void setPassword(string password);
};
