#include <string>
#define STARTING_HP 100
#define STARTING_MONEY 500

class PlayerState {

private:

	int hp;
	int money;
	bool isSupported;
	bool isWinner;

	int player_id;

	std::string bool_to_string(bool my_bool);

public:

    PlayerState(int id);

	std::string serialize(std::string& str);

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
