class RegisterManager {

private:
	RegisterUI registerUI;

public:
	void attemptRegister(Credentials credentials);

	bool checkCredentialsValidity(Credentials credentials);
};
