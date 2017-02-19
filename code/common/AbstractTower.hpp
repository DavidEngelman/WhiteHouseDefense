#ifndef PROJET_ABSTRACTTOWER_H
#define PROJET_ABSTRACTTOWER_H

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

	void setPrice(int price);

	Position getPosition() const;

	void setPosition(int x, int y);
};

#endif // PROJET_ABSTRACTTOWER_H
