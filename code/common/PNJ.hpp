#include "Position.hpp"

#ifdef PROJET_PNJ_H
#define PROJET_PNJ_H

class PNJ{

private:

	int healthPoints;
	int movementSpeed;
	Position position;

public:

    PNJ();

	int getHealthPoints() const;

	void receiveDamage(int damageAmount);

	int getMovementSpeed() const;

	void setMovementSpeed(int movementSpeed);

    void receiveMovementPenalty(int speedReduction);

	Position getPosition() const;

	void setPosition(Position position);
};

#endif // PROJET_PNJ_H
