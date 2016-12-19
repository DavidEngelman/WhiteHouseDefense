class AccountServer : Server {


public:
	void attemptCreateAccount(string name, string password);

	void checkCredentials(string name, string password);
};
