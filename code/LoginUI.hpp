class LoginUI {

private:

	std::string username_entry;
	std::string password_entry;

public:

	LoginUI() = default;
	std::string get_username_entry() { return username_entry; };
	std::string get_password_entry() { return password_entry; };
	void ask_username();
	void ask_password();
	void display();
	void displayError();
};
