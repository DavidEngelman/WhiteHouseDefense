class AccountServer : Server {


public:
	void attemptCreateAccount(int name, int password);

	void checkCredentials(int name, int password);
};
