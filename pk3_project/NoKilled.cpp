#include "NoKilled.h"

#pragma region operators

NoKilled NoKilled::operator++(int) //increment the number of destroyed opponents by the player
{
	NoKilled more_enemies = *this;
	nr_enemies_killed++; //variable increment
	text.setString("ENEMIES\nKILLED: " + std::to_string(nr_enemies_killed)); //update the text
	return std::move(more_enemies);
}

#pragma endregion