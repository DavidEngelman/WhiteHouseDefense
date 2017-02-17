un hibclass MatchMaker : Server {

private:
	int pendingMatches;

public:

	void getNewClients();

	void getPendingMatches(string mode);

	void addPendingMatch(string mode);
};
