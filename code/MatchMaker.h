class MatchMaker : Server {

public:
	int pendingMatches;

	void getNewClients();

	void getPendingMatch(int mode);

	void getPendingMatches();

	void setPendingMatches(int pendingMatches);
};
