class PlayerState {

private:

	int hp;
	int money;
	bool isSupported;
	bool isWinner;
	Account account; // pas sur que ce soit tres utile

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

	void decrease_hp(int amount);
    void increase_hp(int amount);

};
