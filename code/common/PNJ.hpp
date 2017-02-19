#ifndef __PNJ__
#define __PNJ__

class PNJ {

private:

	int healthPoints;
	int movementSpeed;
	Position position;

public:

	int getHealthPoints() const;

	void receiveDamage(int damageAmount);

	int getMovementSpeed() const;

	void setMovementSpeed();

    void receiveMovementPenalty(int speedReduction);

	Position getPosition() const;

	void setPosition(int x, int y);
};

#endif
