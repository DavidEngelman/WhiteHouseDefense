#ifndef DEF_ABSTRACTTOWER
#define DEF_ABSTRACTTOWER

#include "../common/Position.hpp"

class AbstractTower {

private:

	int owner; //ID du joueur qui possède la tour
	int price;
	int damage;
	Position position;

public:

	virtual void shoot(PNJ target);

	int getPrice() const;

	void setPrice(int price) const;

	Position getPosition() const;

	void setPosition(int x, int y) const;
};

#endif
