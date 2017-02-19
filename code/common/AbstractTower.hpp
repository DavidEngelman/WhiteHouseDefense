#ifndef PROJET_ABSTRACTTOWER_H
#define PROJET_ABSTRACTTOWER_H

#include "../common/Position.hpp"
#include "PNJ.hpp"

class AbstractTower {

private:

	int owner; //ID du joueur qui possède la tour
	int typeOfTower;
	int price;
	int damage;
	Position position;

public:

	virtual void shoot(PNJ target);

	/* The price of the tower must be a constant in the constructor
	int getPrice() const;

	void setPrice(int price);
	*/

	/* The position is defined in the map class
	Position getPosition() const;

	void setPosition(int x, int y);
	*/
};

#endif // PROJET_ABSTRACTTOWER_H
