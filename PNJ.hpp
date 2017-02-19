#ifndef PNJ_HPP
#define PNJ_HPP

class PNJ {

private:

	int healthPoints;
	int movementSpeed;
	Position position;

public:

    PNJ();

	int getHealthPoints() const;

	void receiveDamage(int damageAmount);

	int getMovementSpeed() const;

	void setMovementSpeed(int newMovementSpeed);

    void receiveMovementPenalty(int speedReduction);

	Position getPosition() const;

	void setPosition(int x, int y);
};

#endif