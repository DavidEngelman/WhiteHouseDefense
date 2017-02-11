class AccountServer : Server {


public:

    void run() override ;

	void attemptCreateAccount(string name, string password);

	void checkCredentials(string name, string password);
};
