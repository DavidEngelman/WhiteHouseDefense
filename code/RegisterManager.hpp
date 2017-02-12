class RegisterManager {

private:
	RegisterUI registerUI;

public:

    RegisterManager() = default;

	void attemptRegister(Credentials credentials);
	bool checkCredentialsValidity(Credentials credentials);
};
