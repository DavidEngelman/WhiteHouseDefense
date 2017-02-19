class PNJ {

private:

	int hp;
	Position positon;

public:

	int getHp();

	void decreaseHp(int damage);

	Position getPosition();

	void setPosition(int x, int y);
};
