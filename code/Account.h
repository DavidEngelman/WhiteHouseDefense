class Account {

private:
	string username;
	string password;
	FriendList friendList;
	int nbOfvictories;
	int nbPnjKilled;

public:
	string getUsername();

	void setUsername(string username);

	FriendList getFriendList();

	void setFriendList(FriendList friendList);

	int getNbOfvictories();

	void setNbOfvictories(int nbOfvictories);

	int getNbPnjKilled();

	void setNbPnjKilled(int nbPnjKilled);

	string getPassword();

	void setPassword(string password);
};
