#include <string>

class PlayerState {

private:

	int hp;
	int money;
	bool isSupported;
	bool isWinner;

	int player_id;

	std::string bool_to_string(bool my_bool);

public:

	std::string serialize();

	int getHp();

	void setHp(int hp);

	int getMoney();

	void earnMoney(int amount);

	void getIsSupported();

	void setIsSupported(bool isSupported);

	void getIsWinner();

	void setIsWinner(bool isWinner);

	void getPlayer_id();

	void setPlayer_id(int newId);

	void spendMoney(int amount);

	void decrease_hp(int amount);
    void increase_hp(int amount);

};
