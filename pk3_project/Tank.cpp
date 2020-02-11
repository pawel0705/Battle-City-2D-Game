#include "Tank.h"

#pragma Class Methods

void Tank::ResetMovement()  //reset the ability to move
{
	MoveUP = true;
	MoveDOWN = true;
	MoveLEFT = true;
	MoveRIGHT = true;
}

#pragma endregion

#pragma region Accessors

void Tank::SetIsAlive(bool isAlive) //set the state of life of the object
{
	this->isAlive = isAlive;
}

void Tank::SetShooted(bool shoot) //set information about whether the object has shot
{
	this->shoot = shoot;
}

int Tank::GetAD() const //read the damage of the object
{
	return this->attack_demage;
}

int Tank::GetDirection() const //read the position of moving the object
{
	return this->direction;
}
 
bool Tank::GetShooted() const //read the state of the shot of the object
{
	return this->shoot;
}

bool Tank::GetIsAlive() const //read the object's life status
{
	return this->isAlive;
}

#pragma endregion