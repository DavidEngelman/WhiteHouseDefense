class PlayerState {

private:
	int hp;
	int money;
	boolean isSupported;
	boolean isWinner;
	Account account;

public:
	int getHp();

	void setHp(int hp);

	int getMoney();

	void earnMoney(int amount);

	void getIsSupported();

	void setIsSupported(int isSupported);

	void getIsWinner();

	void setIsWinner(int isWinner);

	void getAccount();

	void setAccount(int account);

	void spendMoney(int amount);
};
