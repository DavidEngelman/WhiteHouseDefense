class PlayerState {

private:
	int hp;
	int money;
	bool isSupported;
	bool isWinner;
	Account account;

public:
	int getHp();

	void setHp(int hp);

	int getMoney();

	void earnMoney(int amount);

	void getIsSupported();

	void setIsSupported(bool isSupported);

	void getIsWinner();

	void setIsWinner(bool isWinner);

	void getAccount();

	void setAccount(int account);

	void spendMoney(int amount);
};
