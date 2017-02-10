class LoginManager {

private:
	LoginUI loginUI;

public:
	void attemptLogin(string name, string password);

	void checkCredentialsValidity(string name, string password);
};
