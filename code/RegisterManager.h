class RegisterManager {

private:
	RegisterUI registerUI;

public:
	void attemptRegister(int name, int password);

	void checkCredentialsValidity(int name, int password);
};
