#ifndef Tank_hpp
#define Tank_hpp

#include <SFML/Graphics.hpp>

class Tank //basic information about the tank
{
protected:
	int direction = 0; //which direction it is moving
	int movement_counter = 0; //how long it's moving
	int attack_demage = 10; //damage

	bool shoot = false;
	bool MoveUP = true; //motility
	bool MoveDOWN = true;
	bool MoveLEFT = true;
	bool MoveRIGHT = true;
	bool isAlive = true;

public:
	void ResetMovement(); //reset movement

	void SetIsAlive(bool); //accessors
	void SetShooted(bool);

	int GetAD() const;
	int GetDirection() const;
	bool GetShooted() const;
	bool GetIsAlive() const;
};

#endif