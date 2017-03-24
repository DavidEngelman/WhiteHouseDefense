

#ifndef PROJET_PNJ_H
#define PROJET_PNJ_H

#include "../Other/Position.hpp"
#include "../Other/Direction.hpp"
#include "../Other/Map.hpp"
#include "../Other/Constants.hpp"
#include "../Other/Strings.hpp"

class Map;

class PNJ{

protected:

	int healthPoints;
	int quadrant;
    int damage;
	int value;
    int freezeTicksLeft;
    bool inTransition;

	std::string typeOfPNJ;
	Position position;
	Position last_position;
	Position transitionPosition;
    Direction direction;

    void get_forward_direction();
    void get_right_direction();
    void get_left_direction();
    void get_backward_direction();
    void get_random_direction();

public:


	PNJ(int direction);

    PNJ(Position position, int healthPoints, int direction);

    PNJ(Position position, int healthPoints, Position last_pos, int direction);

    virtual ~PNJ() = 0;

	void advance(Map& map);

	int getHealthPoints() const;

	int receiveDamage(int damageAmount);

	bool isDead();

	void setHealthPoints(int newHp);

    bool isInTransition();

	bool isInPlayerBase();

    const std::string& getType();

    const Position& getPosition() const;

    const Position& getTransitionPosition() const;

	void setPosition(Position& position);

    void setTransitionPosition(Position& position);

	bool can_go_forward(Map &map);

	bool can_go_left(Map &map);

	bool can_go_right(Map &map);

    int getQuadrant() const;

    const Position &getLast_position() const;

    void setLast_position(const Position &last_position);

	std::string serialize();

    int getDamage();

	int getValue();

    bool operator==(const PNJ &rhs) const;

    bool operator!=(const PNJ &rhs) const;

	bool can_go_backward(Map &map);

	void freeze();
};

inline PNJ::~PNJ(){}

#endif // PROJET_PNJ_H
