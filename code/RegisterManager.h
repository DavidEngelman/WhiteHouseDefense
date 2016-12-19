class RegisterManager {

private:
	RegisterUI registerUI;

public:
	void attemptRegister(string name, string password);

	bool checkCredentialsValidity(string name, string password);
};
