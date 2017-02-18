#include "../common/Position.hpp"

class Tower {

private:

	int owner; //l'id du joueur qui possède la tour
	int price;
	int attackDamage;
	Position position;

public:
	void shoot(PNJ target);

	int getPrice();

	void setPrice(int price);

	int getAttackDamage();

	void setAttackDamage(int attackDamage);

	Position getPosition();

	void setPosition(int x, int y);
};
