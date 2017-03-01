#include <string>
#define STARTING_HP 100
#define STARTING_MONEY 500

class PlayerState {

private:

	int hp;
	int money;
	int team;
    bool isSupported;
	bool isWinner;
	int pnjKilled;
	int player_id;

    std::string username;


    std::string bool_to_string(bool my_bool);

public:
	PlayerState();
    PlayerState(int id, std::string username);
    PlayerState(int id, std::string username, int team);

	PlayerState(int _player_id, std::string _username, int _money, int _hp, bool _isSupported,
                    bool _isWinner, int _pnjKilled, int _team);

	std::string serialize();

	int getHp();

    std::string & getUsername();

	int getPnjKilled() const;

	void setHp(int hp);

	bool isAlive();

    int getTeam();

	int getMoney();

	void earnMoney(int amount);

	bool getIsSupported();

	void setIsSupported(bool isSupported);

	bool getIsWinner();

	void setIsWinner(bool isWinner);

	int getPlayer_id();

	void setPlayer_id(int newId);

	void spendMoney(int amount);

	void decrease_hp(int amount);
    void increase_hp(int amount);

	void addOneKill();

	void setTeam(int teamNumber);

};
