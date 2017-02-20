#ifndef POSITION_HPP
#define #ifndef POSITION_HPP

class Position { // There is already a struct in the map class

private:

	int _x;
	int _y;

public:

    Position(int x, int y);

	int getX();

	void setX(int x);

	int getY();

	void setY(int y);
};

#endif // POSITION_HPP

#endif
