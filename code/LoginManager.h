class LoginManager {

private:
	LoginUI loginUI;

public:
	void attemptLogin(int name, int password);

	void checkCredentialsValidity(int name, int password);
};
